/**
 * Author Wojciech Domski <Wojciech.Domski@gmail.com>
 * www: www.Domski.pl
 *
 * https://blog.domski.pl/stm32-hal-driver-for-lora-sx1278-wireless-module/
 *
 * work based on DORJI.COM sample code and
 * https://github.com/realspinner/SX1278_LoRa
 *
 * Modified by Lauri Peltonen, 2018
 *   Removed HAL and use the "standard libary"(?)
 *   Moved internal function forward declarations here from header
 *   Removed defaultConfig (which was not default) and everything uses config now
 *   TODO: Make changes to how the delay functions are handled in rx and tx functions, reset and config is ok
 */

#include "SX1278.h"
#include <string.h>

#include "timer.h"

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"

//#include "gpio.h"
//#include "spi.h"

// Forward declarations of internal functions
//hardware
__attribute__ ((weak)) void SX1278_hw_init(SX1278_hw_t * hw);
__attribute__ ((weak)) void SX1278_hw_SetNSS(SX1278_hw_t * hw, int value);
__attribute__ ((weak)) void SX1278_hw_SPICommand(SX1278_hw_t * hw, uint8_t cmd);
__attribute__ ((weak)) uint8_t SX1278_hw_SPIReadByte(SX1278_hw_t * hw);
__attribute__ ((weak)) void SX1278_hw_DelayMs(uint32_t msec);
__attribute__ ((weak)) int SX1278_hw_GetDIO0(SX1278_hw_t * hw);

uint8_t SX1278_SPIRead(SX1278_t * module, uint8_t addr);
void SX1278_SPIWrite(SX1278_t * module, uint8_t addr, uint8_t cmd);
void SX1278_SPIBurstRead(SX1278_t * module, uint8_t addr, uint8_t *rxBuf,
		uint8_t length);
void SX1278_SPIBurstWrite(SX1278_t * module, uint8_t addr, uint8_t *txBuf,
		uint8_t length);
// void SX1278_DIO0_InterruptHandler(SX1278_t * module);

void SX1278_entryLoRa(SX1278_t * module);
void SX1278_clearLoRaIrq(SX1278_t * module);
int SX1278_LoRaEntryRx(SX1278_t * module, uint8_t length, uint32_t timeout);
uint8_t SX1278_LoRaRxPacket(SX1278_t * module);
int SX1278_LoRaEntryTx(SX1278_t * module, uint8_t length, uint32_t timeout);
int SX1278_LoRaTxPacket(SX1278_t * module, uint8_t *txBuf, uint8_t length, uint32_t timeout);

//////////////////////////////////
// logic
//////////////////////////////////

__attribute__ ((weak)) void SX1278_hw_init(SX1278_hw_t * hw) {
	SX1278_hw_SetNSS(hw, 1);
	GPIO_WriteBit(hw->reset.port, hw->reset.pin, Bit_SET);
}

__attribute__ ((weak)) void SX1278_hw_SetNSS(SX1278_hw_t * hw, int value) {
	GPIO_WriteBit(hw->nss.port, hw->nss.pin,
			(value == 1) ? Bit_SET : Bit_RESET);
}

__attribute__ ((weak)) void SX1278_hw_Reset(SX1278_hw_t * hw) {
	SX1278_hw_SetNSS(hw, 1);
	GPIO_WriteBit(hw->reset.port, hw->reset.pin, Bit_RESET);
	SX1278_hw_DelayMs(1);
	GPIO_WriteBit(hw->reset.port, hw->reset.pin, Bit_SET);
	SX1278_hw_DelayMs(100);
}

__attribute__ ((weak)) void SX1278_hw_SPICommand(SX1278_hw_t * hw, uint8_t cmd) {
	SX1278_hw_SetNSS(hw, 0);

	// Empty the SPI read buffer first
	while(hw->spi->SR & SPI_SR_RXNE) SPI_I2S_ReceiveData(hw->spi);

	SPI_I2S_SendData(hw->spi, cmd);	// Just send one byte
	while(hw->spi->SR & SPI_SR_BSY);	// Wait until transmitted
	while(!(hw->spi->SR & SPI_SR_RXNE));	// Wait until data in receive
	SPI_I2S_ReceiveData(hw->spi);			// Read byte from fifo and discard
}

__attribute__ ((weak)) uint8_t SX1278_hw_SPIReadByte(SX1278_hw_t * hw) {
	uint8_t txByte = 0x00;
	uint8_t rxByte = 0x00;

	// Empty the SPI read buffer first
	while(hw->spi->SR & SPI_SR_RXNE) SPI_I2S_ReceiveData(hw->spi);

	SX1278_hw_SetNSS(hw, 0);
	SPI_I2S_SendData(hw->spi, txByte);
	while(hw->spi->SR & SPI_SR_BSY);	// Wait until transmitted
	while(!(hw->spi->SR & SPI_SR_RXNE));	// Wait until data in receive
	rxByte = SPI_I2S_ReceiveData(hw->spi) & 0xFF;	// Data
	return rxByte;
}

__attribute__ ((weak)) void SX1278_hw_DelayMs(uint32_t msec) {
	//HAL_Delay(msec);
	// TODO: Add delay funtion??
	rfTimer = msec;
	while(rfTimer);
}

__attribute__ ((weak)) int SX1278_hw_GetDIO0(SX1278_hw_t * hw) {
	if(!hw->dio0.port) return 0;
	return (GPIO_ReadInputDataBit(hw->dio0.port, hw->dio0.pin) != 0);
}

//////////////////////////////////
// logic
//////////////////////////////////

uint8_t SX1278_SPIRead(SX1278_t * module, uint8_t addr) {
	uint8_t tmp;
	SX1278_hw_SPICommand(module->hw, addr);
	tmp = SX1278_hw_SPIReadByte(module->hw);
	SX1278_hw_SetNSS(module->hw, 1);
	return tmp;
}

void SX1278_SPIWrite(SX1278_t * module, uint8_t addr, uint8_t cmd) {
	SX1278_hw_SetNSS(module->hw, 0);
	SX1278_hw_SPICommand(module->hw, addr | 0x80);
	SX1278_hw_SPICommand(module->hw, cmd);
	SX1278_hw_SetNSS(module->hw, 1);
}

void SX1278_SPIBurstRead(SX1278_t * module, uint8_t addr, uint8_t* rxBuf,
		uint8_t length) {
	uint8_t i;
	if (length <= 1) {
		return;
	} else {
		SX1278_hw_SetNSS(module->hw, 0);
		SX1278_hw_SPICommand(module->hw, addr);
		for (i = 0; i < length; i++) {
			*(rxBuf + i) = SX1278_hw_SPIReadByte(module->hw);
		}
		SX1278_hw_SetNSS(module->hw, 1);
	}
}

void SX1278_SPIBurstWrite(SX1278_t * module, uint8_t addr, uint8_t* txBuf,
		uint8_t length) {
	unsigned char i;
	if (length <= 1) {
		return;
	} else {
		SX1278_hw_SetNSS(module->hw, 0);
		SX1278_hw_SPICommand(module->hw, addr | 0x80);
		for (i = 0; i < length; i++) {
			SX1278_hw_SPICommand(module->hw, *(txBuf + i));
		}
		SX1278_hw_SetNSS(module->hw, 1);
	}
}

void SX1278_config(SX1278_t * module) {
	uint8_t frequency = module->frequency;
	uint8_t power = (module->power <= SX1278_POWER_11DBM) ? module->power : SX1278_POWER_11DBM;
	uint8_t LoRa_Rate = (module->LoRa_Rate <= SX1278_LORA_SF_12) ? module->LoRa_Rate : SX1278_LORA_SF_12;
	uint8_t LoRa_BW = (module->LoRa_BW <= SX1278_LORA_BW_500KHZ) ? module->LoRa_BW : SX1278_LORA_BW_500KHZ;
	uint8_t LoRa_CR = (module->LoRa_CR <= SX1278_LORA_CR8) ? module->LoRa_CR : SX1278_LORA_CR8;
	uint8_t LoRa_CRC = module->LoRa_CRC ? 0x01 : 0x00;
	uint16_t LoRa_preamble = (module->LoRa_preamble < 6) ? 6 : module->LoRa_preamble;

	SX1278_sleep(module); //Change modem mode Must in Sleep mode
	SX1278_hw_DelayMs(15);

	SX1278_entryLoRa(module);
	//SX1278_SPIWrite(module, 0x5904); //?? Change digital regulator form 1.6V to 1.47V: see errata note

	SX1278_SPIBurstWrite(module, LR_RegFrMsb,
			(uint8_t*) SX1278_Frequency[frequency], 3); //setting  frequency parameter

	//setting base parameter
	SX1278_SPIWrite(module, LR_RegPaConfig, SX1278_Power[power]); //Setting output power parameter

	SX1278_SPIWrite(module, LR_RegOcp, 0x0B);			//RegOcp,Close Ocp
	SX1278_SPIWrite(module, LR_RegLna, 0x23);		//RegLNA,High & LNA Enable
	if (LoRa_Rate == SX1278_LORA_SF_6) {	// Spreading factor 6 is a special high speed case
		// Set SpreadingFactor = 6 in RegModemConfig2
		// The header must be set to Implicit mode.
		// Set the bit field DetectionOptimize of register RegLoRaDetectOptimize to value "0b101".
		// Write 0x0C in the register RegDetectionThreshold
		uint8_t tmp;
		SX1278_SPIWrite(module,
				LR_RegModemConfig1,
				((SX1278_LoRaBandwidth[LoRa_BW] << 4) + (SX1278_LoraErrorCodingRate[LoRa_CR] << 1) + 0x01)); // 0x01 = Implicit header mode

		SX1278_SPIWrite(module,
				LR_RegModemConfig2,
				((SX1278_SpreadFactor[LoRa_Rate] << 4) + (LoRa_CRC << 2) + 0x03));	// TODO: What is 0x03???

		tmp = SX1278_SPIRead(module, LR_RegDetectOptimize);
		tmp &= 0xF8;
		tmp |= 0x05;
		SX1278_SPIWrite(module, LR_RegDetectOptimize, tmp);
		SX1278_SPIWrite(module, LR_RegDetectionThreshold, 0x0C);

	} else {	// Other spreading factors
		SX1278_SPIWrite(module,
				LR_RegModemConfig1,
				((SX1278_LoRaBandwidth[LoRa_BW] << 4) + (SX1278_LoraErrorCodingRate[LoRa_CR] << 1) + 0x00)); // 0x00 = Explicit header

		SX1278_SPIWrite(module,
				LR_RegModemConfig2,
				((SX1278_SpreadFactor[LoRa_Rate] << 4) + (LoRa_CRC << 2)
						+ 0x03)); //SFactor &  LNA gain set by the internal AGC loop
	}

	SX1278_SPIWrite(module, LR_RegSymbTimeoutLsb, 0xFF); //RegSymbTimeoutLsb Timeout = 0x3FF(Max)
	SX1278_SPIWrite(module, LR_RegPreambleMsb, (LoRa_preamble >> 8) & 0xFF); // RegPreambleMsb
	SX1278_SPIWrite(module, LR_RegPreambleLsb, LoRa_preamble & 0xFF); // RegPreambleLsb + 4 = total Preamble
	SX1278_SPIWrite(module, REG_LR_DIOMAPPING2, 0x01); //RegDioMapping2 DIO5=00, DIO4=01
	module->readBytes = 0;

	SX1278_standby(module); //Entry standby mode
}

void SX1278_standby(SX1278_t * module) {
	SX1278_SPIWrite(module, LR_RegOpMode, (SX1278_SPIRead(module, LR_RegOpMode) & 0xF8) | STANDBY_MODE);
	module->status = STANDBY;
}

void SX1278_sleep(SX1278_t * module) {
	SX1278_SPIWrite(module, LR_RegOpMode, (SX1278_SPIRead(module, LR_RegOpMode) & 0xF8) | SLEEP_MODE);
	module->status = SLEEP;
}

void SX1278_entryLoRa(SX1278_t * module) {
	SX1278_sleep(module);
	SX1278_SPIWrite(module, LR_RegOpMode, (SX1278_SPIRead(module, LR_RegOpMode) & 0x7F) | LORA_MODE);
}

void SX1278_clearLoRaIrq(SX1278_t * module) {
	SX1278_SPIWrite(module, LR_RegIrqFlags, 0xFF);
}

int SX1278_LoRaEntryRx(SX1278_t * module, uint8_t length, uint32_t timeout) {
	uint8_t addr;

	module->packetLength = length;

	if(module->status != STANDBY)
		SX1278_standby(module);

	//SX1278_config(module);		//Setting base parameter
	SX1278_SPIWrite(module, REG_LR_PADAC, (SX1278_SPIRead(module, REG_LR_PADAC) & 0xF8) | 0x04);	//Normal and RX
	//SX1278_SPIWrite(module, LR_RegHopPeriod, 0xFF);	//No FHSS
	SX1278_SPIWrite(module, REG_LR_DIOMAPPING1, 0x01);//DIO=00,DIO1=00,DIO2=00, DIO3=01
	SX1278_SPIWrite(module, LR_RegIrqFlagsMask, 0x1F);//Open RxDone interrupt & Timeout & CRC Error
	SX1278_clearLoRaIrq(module);
	SX1278_SPIWrite(module, LR_RegPayloadLength, length); // Payload length (for implicit header)
	addr = SX1278_SPIRead(module, LR_RegFifoRxBaseAddr); //Read RxBaseAddr
	SX1278_SPIWrite(module, LR_RegFifoAddrPtr, addr); //RxBaseAddr->FiFoAddrPtr
	SX1278_SPIWrite(module, LR_RegOpMode, (SX1278_SPIRead(module, LR_RegOpMode) & 0xF8) | RXCONT_MODE);	//Mode//Low Frequency Mode
	//SX1278_SPIWrite(module, LR_RegOpMode,0x05);	//Continuous Rx Mode //High Frequency Mode
	module->readBytes = 0;

	while (1) {
		if ((SX1278_SPIRead(module, LR_RegModemStat) & 0x04) == 0x04) {	//Rx-on going RegModemStat
			module->status = RX;
			return 1;
		}
		if (--timeout == 0) {
			SX1278_hw_Reset(module->hw);
			SX1278_config(module);
			return 0;
		}
		SX1278_hw_DelayMs(1);
	}
}

uint8_t SX1278_LoRaRxPacket(SX1278_t * module) {
	unsigned char addr;
	unsigned char packet_size;

	if (SX1278_hw_GetDIO0(module->hw)) {
		memset(module->rxBuffer, 0x00, SX1278_MAX_PACKET);

		addr = SX1278_SPIRead(module, LR_RegFifoRxCurrentaddr); //last packet addr
		SX1278_SPIWrite(module, LR_RegFifoAddrPtr, addr); //RxBaseAddr -> FiFoAddrPtr

		if (module->LoRa_Rate == SX1278_LORA_SF_6) { //When SpreadFactor is six,will used Implicit Header mode(Excluding internal packet length)
			packet_size = module->packetLength;
		} else {
			packet_size = SX1278_SPIRead(module, LR_RegRxNbBytes); //Number for received bytes
		}

		SX1278_SPIBurstRead(module, 0x00, module->rxBuffer, packet_size);
		module->readBytes = packet_size;

		// Update status
		module->rssi = SX1278_PktRSSI_LoRa(module);
		module->snr = SX1278_PktSNR_LoRa(module);
		module->crc = SX1278_PktCRCOk_LoRa(module);

		SX1278_clearLoRaIrq(module);
	}
	return module->readBytes;
}

// TODO: Fix the waiting in this function, and the reset if send was not ok
int SX1278_LoRaEntryTx(SX1278_t * module, uint8_t length, uint32_t timeout) {
	uint8_t addr;
	uint8_t temp;

	module->packetLength = length;

	if(module->status != STANDBY)
		SX1278_standby(module);

	// TODO: Low data rate optimize?

	//SX1278_config(module); //setting base parameter	// This must have been called earlier!!
	SX1278_SPIWrite(module, REG_LR_PADAC, SX1278_SPIRead(module, REG_LR_PADAC) | 0x07);	// Tx for 20dBm
	//SX1278_SPIWrite(module, LR_RegHopPeriod, 0x00); //RegHopPeriod NO FHSS
	SX1278_SPIWrite(module, REG_LR_DIOMAPPING1, 0x41); //DIO0=01, DIO1=00,DIO2=00, DIO3=01
	SX1278_clearLoRaIrq(module);
	SX1278_SPIWrite(module, LR_RegIrqFlagsMask, 0xF7); //Open TxDone interrupt
	SX1278_SPIWrite(module, LR_RegPayloadLength, length); // Payload length
	addr = SX1278_SPIRead(module, LR_RegFifoTxBaseAddr); // RegFiFoTxBaseAddr
	SX1278_SPIWrite(module, LR_RegFifoAddrPtr, addr); //RegFifoAddrPtr

	while (1) {
		temp = SX1278_SPIRead(module, LR_RegPayloadLength);
		if (temp == length) {
			module->status = TX;
			return 1;
		}

		if (--timeout == 0) {
			SX1278_hw_Reset(module->hw);
			SX1278_config(module);
			return 0;
		}
	}
}

// TODO: Fix the waiting in this function, and the reset if send was not ok
int SX1278_LoRaTxPacket(SX1278_t * module, uint8_t* txBuffer, uint8_t length,
		uint32_t timeout) {
	SX1278_SPIBurstWrite(module, 0x00, txBuffer, length);
	SX1278_SPIWrite(module, LR_RegOpMode, (SX1278_SPIRead(module, LR_RegOpMode) & 0xF8) | TX_MODE);	// Tx Mode

	while (1) {
		if (SX1278_hw_GetDIO0(module->hw)) { //if(Get_NIRQ()) //Packet send over
			SX1278_SPIRead(module, LR_RegIrqFlags);
			SX1278_clearLoRaIrq(module); //Clear irq
			SX1278_standby(module); //Entry Standby mode
			return 1;
		}

		if (--timeout == 0) {
			SX1278_hw_Reset(module->hw);
			SX1278_config(module);
			return 0;
		}
		SX1278_hw_DelayMs(1);
	}
}

void SX1278_begin(SX1278_t * module) {
	SX1278_hw_init(module->hw);
	SX1278_config(module);
}

int SX1278_transmit(SX1278_t * module, uint8_t* txBuf, uint8_t length,
		uint32_t timeout) {
	if (SX1278_LoRaEntryTx(module, length, timeout)) {
		return SX1278_LoRaTxPacket(module, txBuf, length, timeout);
	}
	return 0;
}

int SX1278_receive(SX1278_t * module, uint8_t length, uint32_t timeout) {
	return SX1278_LoRaEntryRx(module, length, timeout);
}

uint8_t SX1278_available(SX1278_t * module) {
	return SX1278_LoRaRxPacket(module);
}

// Note: Clears the buffer even though might not read everything...
uint8_t SX1278_read(SX1278_t * module, uint8_t* rxBuf, uint8_t length) {
	if (length > module->readBytes)
		length = module->readBytes;

	if(length > SX1278_MAX_PACKET)
		length = SX1278_MAX_PACKET;

	memcpy(rxBuf, module->rxBuffer, length);
	rxBuf[length] = '\0';
	module->readBytes = 0;
	return length;
}

uint8_t SX1278_RSSI_LoRa(SX1278_t * module) {
	uint32_t temp = 10;
	temp = SX1278_SPIRead(module, LR_RegRssiValue); //Read RegRssiValue, Rssi value
	//temp = temp + 127 - 137; //127:Max RSSI, 137:RSSI offset
	return (uint8_t) temp;
}

uint8_t SX1278_PktRSSI_LoRa(SX1278_t * module) { // RSSI of last received packet
	return SX1278_SPIRead(module, LR_RegPktRssiValue);
}

int8_t SX1278_PktSNR_LoRa(SX1278_t * module) { // SNR of last received packet, signed
	return SX1278_SPIRead(module, LR_RegPktSnrValue);
}

uint8_t SX1278_PktCRCOk_LoRa(SX1278_t * module) { // LoRa packet CRC was ok or not?
	return SX1278_SPIRead(module, LR_RegIrqFlags) & 0x20;
}

uint8_t SX1278_RSSI(SX1278_t * module) {	// FSK/OOK mode
	uint8_t temp = 0xff;
	temp = SX1278_SPIRead(module, 0x11);
	temp = 127 - (temp >> 1);	//127:Max RSSI
	return temp;
}


// Temperature correction offset, must be measured externally
static signed char temperature_offset = 4;

signed char SX1278_read_temperature(SX1278_t * module)
{
	uint8_t imageCal;
	uint8_t raw_temp;
	uint8_t opMode;

	//if(module->status != STANDBY)
	//	return 0xFF;	// Indicates error

	// Read operating mode
	opMode = SX1278_SPIRead(module, LR_RegOpMode);

	// Go to sleep mode
	SX1278_sleep(module);

	// Go to FSK/OOK mode and RXSynth mode
	if(opMode & LORA_MODE)
		SX1278_SPIWrite(module, LR_RegOpMode, 0x00);	// FSK/OOK mode (bit 7 cleared = FSK/OOK, bits 2-0 cleared = sleep

	SX1278_SPIWrite(module, LR_RegOpMode, FSRX_MODE);	// Just set the mode bits to RX synth

	// Enable temperature reading
	imageCal = SX1278_SPIRead(module, RegImageCal);
	SX1278_SPIWrite(module, RegImageCal, imageCal & 0xFE);	// Clear bit 0 = temperature reading enabled

	// Wait > 140 us for stable reading
	SX1278_hw_DelayMs(1);	// TODO: Convert delay to us for shorter delay?

	// Disable temperature reading
	SX1278_SPIWrite(module, RegImageCal, imageCal | 0x01);	// Set bit 0 = temperature reading disabled

	// Go to sleep mode
	SX1278_sleep(module);

	// Read sensor
	raw_temp = SX1278_SPIRead(module, RegTemp);

	// Back to LoRa mode if was set before (must be set separately in sleep mode)
	if(opMode & LORA_MODE)
		SX1278_SPIWrite(module, LR_RegOpMode, LORA_MODE);

	// Set all other previous bits
	SX1278_SPIWrite(module, LR_RegOpMode, opMode);

	// Back to standby mode
	// Should have been set by previous bits already...
	//SX1278_standby(module);

	// Convert to signed temperature reading
	if(raw_temp & 0x80)
		module->temperature = 255 - raw_temp;
	else
		module->temperature = -raw_temp;

	// Apply correction offset
	module->temperature += temperature_offset;

	return module->temperature;
}
