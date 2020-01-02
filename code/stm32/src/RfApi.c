/*
 * Smart remote socket RF module API
 * Currently supports only sx1278
 * Copyright (C) 2018 Lauri Peltonen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "RfApi.h"

#include "SX1278.h"

#include "RelayControl.h"
#include "Scheduler.h"
#include "Timer.h"
#include "Temperature.h"

static SX1278_hw_t sx1278_dev;
SX1278_t sx1278_rf;
//volatile uint8_t databyte;

// Initialize all hardware
void SX1278_HWMainInit(void)
{
	// Based on https://blog.mark-stevens.co.uk/2014/03/spi-stm32/

	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStruct;

	//  Initialise the peripheral clocks.
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

	// Configure output pins used by SPI1:
	//  PA5 = SCLK
	//  PA7 = MOSI
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// Configure input pins used by SPI
	//  PA6 = MISO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // TODO: Pull-up or down or none?
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// Configure generic outputs
	//  PA8 = DIO0
	//	PA4 = CSN / NSS (Chip select)
	//  PA3 = reset
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_4 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// Enable SPI

	// Connect SPI1 pins to SPI alternate function.
	// TODO: Check, but this seems to remap from PA4 -> PA15 etc
	// i.e. should not be used since we used the default SPI pinout
	GPIO_PinRemapConfig(GPIO_Remap_SPI1, DISABLE);

	//    Set PA4 high as we will be using active low for the
	//    device select.
	GPIO_SetBits(GPIOA, GPIO_Pin_4);

	//     Enable the SPI peripheral clock.
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	// SX1278 documentation:
	// The SPI interface gives access to the configuration register via a synchronous full-duplex protocol corresponding to
	// CPOL = 0 and CPHA = 0 in Motorola/Freescale nomenclature. Only the slave side is implemented.
	// Single, burst and FIFO
	// Maximum 10 MHz SPI clock speed
	//
	// Configure SPI1 in Mode 0:
	//  CPOL = 0 --> clock is low when idle
	//  CPHA = 0 --> data is sampled at the first edge
	//
	//  SPI Master mode, 8 bits of data, clock prescalar is 256, MSB is
	//  transmitted first.
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft /*| SPI_NSSInternalSoft_Set*/; // Can be only soft or hard
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;	// At 72 MHz this results in 562.5 kHz SPI
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 0x0007;		// Default value
	SPI_Init(SPI1, &SPI_InitStruct);

	//    Enable SPI.
    SPI_Cmd(SPI1, ENABLE);

    // Fill in the sx1278 structure
    // Hardware config
    sx1278_dev.reset.port = GPIOA;
    sx1278_dev.reset.pin = GPIO_Pin_3;
    sx1278_dev.dio0.port = GPIOA;
    sx1278_dev.dio0.pin = GPIO_Pin_8;
    sx1278_dev.nss.port = GPIOA;
    sx1278_dev.nss.pin = GPIO_Pin_4;
	sx1278_dev.spi = SPI1;

	sx1278_rf.hw = &sx1278_dev;

	// Reset
	SX1278_hw_Reset(&sx1278_dev);

	// Radio config
	// Set spreading factor to 12 to have maximum SNR, i.e. receiver sensitivity
	// Bandwidth 62.5 kHz to allow use of crystal instead of TCXO
	// 14 dBm = 25 mW transmit power
	// Default packet length 16 bytes
	//SX1278_begin(&sx1278_rf, SX1278_434MHZ, SX1278_POWER_14DBM, SX1278_LORA_SF_12, SX1278_LORA_BW_62_5KHZ, 16);
	//SX1278_begin(&sx1278_rf, SX1278_434MHZ, SX1278_POWER_14DBM, SX1278_LORA_SF_8, SX1278_LORA_BW_62_5KHZ, 16);	// Original
	sx1278_rf.frequency = SX1278_434MHZ;
	sx1278_rf.power = SX1278_POWER_14DBM;
	sx1278_rf.LoRa_Rate = SX1278_LORA_SF_8;
	sx1278_rf.LoRa_BW = SX1278_LORA_BW_62_5KHZ;
	sx1278_rf.LoRa_CR = SX1278_LORA_CR8;
	sx1278_rf.LoRa_CRC = 1;
	sx1278_rf.LoRa_preamble = 6;
	sx1278_rf.packetLength = 16;
	SX1278_begin(&sx1278_rf);

	// TEST: Read register, should return 106 = 0x6C
	//databyte = SX1278_SPIRead(&sx1278_rf, LR_RegFrMsb);

	// Enter receive mode by default
	// 16 bytes receive length, 2000 (units) timeout in initialization(?)
	SX1278_receive(&sx1278_rf, 16, 2000);
}



// Loop
static enum rfState {IDLE = 0, PARSE, EXECUTE, WAIT_FOR_TX, DO_TX, WAIT_AFTER_TX} rf_state = IDLE;

#define RF_MAX_COMMAND		(64)
static uint8_t rf_buffer[RF_MAX_COMMAND] = {0};
static uint8_t rf_read_len = 0;

static struct _rfCommand {
	uint32_t time1;
	uint32_t time2;
	uint8_t command;
	uint8_t flags;
	uint8_t package_num;
	uint8_t retransmit_num;
	uint8_t spare1;
	uint8_t spare2;
	uint8_t spare3;
	uint8_t spare4;
} rf_command;
#define RF_COMMAND_LEN	(16)
#if RF_COMMAND_LEN > RF_MAX_COMMAND
#error RF command length > max command length
#endif


// Struct holding the system status, if requested
static struct _rfStatus {
	uint32_t time;			// Current RTC time
	uint8_t relays;			// Relay status byte
	int8_t temperature;		// Measured temperature in degC
	uint8_t command_status;	// Status of last command
	int8_t rf_snr;			// SNR of last packet received
	uint8_t rf_rssi;		// RSSI of last packet received
	uint8_t rf_channel;		// RF channel
	uint8_t rf_power;		// RF transmit power
	uint8_t last_package;	// Last package num. received
	uint8_t retransmits;	// Number of retransmits received
	uint8_t reserved1;
	uint8_t reserved2;
	uint8_t reserved3;
	uint32_t custom_data;	// Custom data for some request
} rf_status;

#define RF_STATUS_LEN	(16)
#if RF_STATUS_LEN > RF_MAX_COMMAND
#error RF status length > max command length
#endif

#define COMMAND_RELAY1_ON		(1)
#define COMMAND_RELAY1_OFF		(2)
#define COMMAND_RELAY1_TOGGLE	(3)
#define COMMAND_RELAY2_ON		(5)
#define COMMAND_RELAY2_OFF		(6)
#define COMMAND_RELAY2_TOGGLE	(7)

#define COMMAND_RELAY1_TIMED	(20)
#define COMMAND_RELAY2_TIMED	(21)
#define COMMAND_RELAY1_TEMP		(25)
#define COMMAND_RELAY2_TEMP		(26)
#define COMMAND_TIMED_CLEAR		(30)


#define COMMAND_REQUEST_STATUS	(100)

#define COMMAND_SCHED_EVENTS	(105)
#define COMMAND_SCHED_EVENT_TYPE	(106)	// Request event info
#define COMMAND_SCHED_EVENT_TIME	(107)
#define COMMAND_SCHED_EVENT_BLOCK	(108)

#define COMMAND_SET_TIME		(120)
#define COMMAND_SET_DST_START	(130)
#define COMMAND_SET_DST_STOP	(131)

#define COMMAND_SET_FREQ		(200)	// Set RF frequency
#define COMMAND_SET_POWER		(205)	// Set RF transmit power


// Initialize
void rf_init(void)
{
	SX1278_HWMainInit();

	rf_status.last_package = 0;
	rf_status.retransmits = 0;
}


void rf_update(void)
{
	uint8_t bytes;
	uint8_t status = 0;
	uint8_t schedid1, schedid2;

	switch(rf_state) {
	case IDLE:
		// Check if message arrived, and fetch it
		if((bytes = rf_available()))
		{
			rf_read_len = rf_read(&rf_buffer[0], RF_MAX_COMMAND);

			// Wrong amount of data -> return without doing anything
			if(rf_read_len != RF_COMMAND_LEN)
				break;

			// TODO: Check CRC

			rf_state = PARSE;
		}
		break;


	case PARSE:
		rf_command.command = rf_buffer[0];
		rf_command.flags = rf_buffer[1];
		rf_command.spare1 = rf_buffer[2];
		rf_command.spare2 = rf_buffer[3];
		rf_command.time1 = (uint32_t)((rf_buffer[4] << 24) + (rf_buffer[5] << 16) + (rf_buffer[6] << 8) + rf_buffer[7]);
		rf_command.time2 = (uint32_t)((rf_buffer[8] << 24) + (rf_buffer[9] << 16) + (rf_buffer[10] << 8) + rf_buffer[11]);
		rf_command.spare3 = rf_buffer[12];
		rf_command.spare4 = rf_buffer[13];
		// rf_buffer[14];
		rf_command.package_num = rf_buffer[15] & 0xF8;
		rf_command.retransmit_num = rf_buffer[15] & 0x07;

		rf_state = EXECUTE;
		break;

	case EXECUTE:
		if(rf_command.package_num == rf_status.last_package)
		{
			// This package is a retransmit of an older one, do not do anything to it
			// However, send back the same reply as earlier
			if(rf_status.retransmits < 0x07) rf_status.retransmits++;
		}
		else
		{
			// New command package, handle it
			rf_status.last_package = rf_command.package_num;
			rf_status.retransmits = 0;

			// Clear the custom data buffer
			rf_status.custom_data = 0;

			switch(rf_command.command) {
			case COMMAND_RELAY1_ON:
				status = relay_control_on(0);
				break;
			case COMMAND_RELAY1_OFF:
				status = relay_control_off(0);
				break;
			case COMMAND_RELAY1_TOGGLE:
				status = relay_control_toggle(0);
				break;
			case COMMAND_RELAY2_ON:
				status = relay_control_on(1);
				break;
			case COMMAND_RELAY2_OFF:
				status = relay_control_off(1);
				break;
			case COMMAND_RELAY2_TOGGLE:
				status = relay_control_toggle(1);
				break;
			case COMMAND_RELAY1_TIMED:
				schedid1 = scheduler_add(rf_command.time1, SCHED_MODE_ON);
				schedid2 = scheduler_add(rf_command.time2, SCHED_MODE_OFF);

				if(schedid1 == SCHED_NO_EVENT || schedid2 == SCHED_NO_EVENT)
				{
					// Error, clear both. No need to call finish since nothing changed
					scheduler_remove(schedid1);
					scheduler_remove(schedid2);
					status = 0;
				}
				else
				{
					// Update scheduler and correct status
					scheduler_finish();
					status = 1;
				}
				break;
			case COMMAND_RELAY2_TIMED:
				schedid1 = scheduler_add(rf_command.time1, SCHED_MODE_ON | SCHED_RELAY2);
				schedid2 = scheduler_add(rf_command.time2, SCHED_MODE_OFF | SCHED_RELAY2);

				if(schedid1 == SCHED_NO_EVENT || schedid2 == SCHED_NO_EVENT)
				{
					// Error, clear both. No need to call finish since nothing changed
					scheduler_remove(schedid1);
					scheduler_remove(schedid2);
					status = 0;
				}
				else
				{
					// Update scheduler and correct status
					scheduler_finish();
					status = 1;
				}
				break;
			case COMMAND_RELAY1_TEMP:
				schedid1 = scheduler_add(rf_command.time1, SCHED_MODE_ON | SCHED_USE_TEMPERATURE);

				if(schedid1 == SCHED_NO_EVENT)
				{
					// Error
					status = 0;
				}
				else
				{
					// Update scheduler and correct status
					scheduler_finish();
					status = 1;
				}
				break;
			case COMMAND_RELAY2_TEMP:
				schedid1 = scheduler_add(rf_command.time1, SCHED_MODE_ON | SCHED_USE_TEMPERATURE | SCHED_RELAY2);

				if(schedid1 == SCHED_NO_EVENT)
				{
					// Error
					status = 0;
				}
				else
				{
					// Update scheduler and correct status
					scheduler_finish();
					status = 1;
				}
				break;
			case COMMAND_TIMED_CLEAR:
				scheduler_clear();
				status = 1;
				break;
			case COMMAND_SET_TIME:
				RTC_set_time(rf_command.time1);
				status = 1;
				break;
			case COMMAND_SET_DST_START:
				// TODO: Implement
				break;
			case COMMAND_SET_DST_STOP:
				// TODO: Implement
				break;
			case COMMAND_SCHED_EVENTS:
				rf_status.custom_data = SCHED_MAX_EVENTS;
				status = 1;
				break;
			case COMMAND_SCHED_EVENT_TYPE:
				rf_status.custom_data = scheduler_event_type(rf_command.flags);
				status = 1;
				break;
			case COMMAND_SCHED_EVENT_TIME:
				rf_status.custom_data = scheduler_event_time(rf_command.flags);
				status = 1;
				break;
			case COMMAND_SCHED_EVENT_BLOCK:
				status = scheduler_block(rf_command.flags);
				break;
			case COMMAND_REQUEST_STATUS:
				// Add some more data to custom data fields
				// Lowest bytes of custom data is radio module temperature
				rf_status.custom_data = (unsigned char)(sx1278_rf.temperature);

				// Then processor supply voltage, scaled so that 255 = 5.1 V (20x scaling)
				rf_status.custom_data |= supply_voltage() << 8;

				status = 1;
				break;
			default:
				break;
			};

			rf_status.command_status = status;
		}

		// Initialize timer this uses same timer as SX1278
		// but as this API is the only one calling SX1278, it is ok for now..
		rfTimer = 10;		// Wait 10 ms

		rf_state = WAIT_FOR_TX;
		break;

	case WAIT_FOR_TX:
		// After timed delay, transmit reply
		if(!rfTimer)
			rf_state = DO_TX;

		break;

	case DO_TX:
		// Fill the status struct
		rf_update_status();

		// Parse from struct to command buffer
		rf_buffer[0] = (uint8_t)((rf_status.time >> 24) & 0xFF);
		rf_buffer[1] = (uint8_t)((rf_status.time >> 16) & 0xFF);
		rf_buffer[2] = (uint8_t)((rf_status.time >> 8) & 0xFF);
		rf_buffer[3] = (uint8_t)(rf_status.time & 0xFF);
		rf_buffer[4] = rf_status.command_status;
		rf_buffer[5] = (uint8_t)rf_status.rf_snr;
		rf_buffer[6] = rf_status.rf_rssi;
		rf_buffer[7] = rf_status.rf_channel;
		rf_buffer[8] = rf_status.rf_power;
		rf_buffer[9] = rf_status.relays;
		rf_buffer[10] = (uint8_t)rf_status.temperature;
		rf_buffer[11] = (uint8_t)((rf_status.custom_data >> 24) & 0xFF);
		rf_buffer[12] = (uint8_t)((rf_status.custom_data >> 16) & 0xFF);
		rf_buffer[13] = (uint8_t)((rf_status.custom_data >> 8) & 0xFF);
		rf_buffer[14] = (uint8_t)(rf_status.custom_data & 0xFF);
		rf_buffer[15] = (uint8_t)((rf_status.last_package & 0xF8) | (rf_status.retransmits & 0x07));

		// Transmit buffer
		if(rf_transmit(&rf_buffer[0], RF_STATUS_LEN, 2000) == 0)
			while(1);

		// Switch back to receive mode
		//rf_mode_receive(2000);
		rfTimer = 10;	// Wait some time after TX

		rf_state = WAIT_AFTER_TX;
		break;

	case WAIT_AFTER_TX:
		if(!rfTimer)
		{
			rf_mode_receive(2000);
			rf_state = IDLE;
		}
		break;

	default:
		break;
	}
}

// Switch to receive mode
uint8_t rf_mode_receive(uint16_t timeout)
{
	return SX1278_receive(&sx1278_rf, 16, timeout);
}

// Returns number of bytes received
uint8_t rf_available(void)
{
	return SX1278_available(&sx1278_rf);
}

// Read bytes
uint8_t rf_read(uint8_t *buffer, uint8_t len)
{
	return SX1278_read(&sx1278_rf, buffer, len);
}

// Transmit bytes
uint8_t rf_transmit(uint8_t *buffer, uint8_t len, uint16_t timeout)
{
	return SX1278_transmit(&sx1278_rf, buffer, len, timeout);
}

// Update status of all subsystems
void rf_update_status(void)
{
	rf_status.time = RTC_current_time();
	rf_status.relays = relay_get_states();

	rf_status.rf_rssi = sx1278_rf.rssi;
	rf_status.rf_snr = sx1278_rf.snr;
	rf_status.rf_channel = sx1278_rf.frequency;
	rf_status.rf_power = sx1278_rf.power;

	rf_status.temperature = temperature_internal(); 	// Latest reading
}

void rf_read_temperature(void)
{
	SX1278_read_temperature(&sx1278_rf);
}

int8_t rf_get_temperature(void)
{
	return sx1278_rf.temperature;
}
