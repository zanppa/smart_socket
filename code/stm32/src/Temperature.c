/*
 * Smart remote socket tmperature measuerement functions
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

#include "RFApi.h"
#include "Temperature.h"

// Internal temperature in deg C
static signed char int_temp = 0;

// Supply voltage in mV
static unsigned short v_supply = 0;

// Define place to store ADC results
#define ADC_CHANNELS		2
static volatile uint16_t adc_results[ADC_CHANNELS];

static volatile unsigned char dma_trigs = 0;

void temperature_init(void)
{
	/*
	The TSVREFE bit must be set to enable both internal channels: ADCx_IN16 (temperature
	sensor) and ADCx_IN17 (VREFINT) conversion.
	. Select the ADCx_IN16 input channel.
	2. Select a sample time of 17.1 µs
	3. Set the TSVREFE bit in the ADC control register 2 (ADC_CR2) to wake up the
	temperature sensor from power down mode.
	4. Start the ADC conversion by setting the ADON bit (or by external trigger).
	5. Read the resulting VSENSE data in the ADC data register
	6. Obtain the temperature using the following formula:
	Temperature (in °C) = {(V25 - VSENSE) / Avg_Slope} + 25.
	Where,
	V
	25 = VSENSE value for 25° C and
	Avg_Slope = Average Slope for curve between Temperature vs. VSENSE (given in
	mV/° C or µV/ °C).
	Refer to the Electrical characteristics section for the actual values of V
	25 and
	Avg_Slope.
	*/

	// APB2 clock runs at 72 MHz
	// Divide ADC clock byt eight
	RCC->CFGR |= RCC_CFGR_ADCPRE_0 | RCC_CFGR_ADCPRE_1;


	// Enable ADC clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	// Select > 17.1 us sampling time (required by internal temp sensor)
	// for channels 16 and 17 (int temp and ref)
	// ADC clock is 72 MHz /8 and time is samples + 12.5 samples
	// select 239.5 samples to get 28 us conv. time
	ADC1->SMPR1 |= ADC_SMPR1_SMP16_0 | ADC_SMPR1_SMP16_1 | ADC_SMPR1_SMP16_2 |
			ADC_SMPR1_SMP17_0 | ADC_SMPR1_SMP17_1 | ADC_SMPR1_SMP17_2;

	// Select internal temperature sensor and Vref
	ADC1->SQR3 = ADC_SQR3_SQ1_4 |	// Channel 16 = int. temp
				ADC_SQR3_SQ2_4 | ADC_SQR3_SQ2_0;	// Channel 17 = int. vref

	// Only 2 channels used at the moment (bit 1 enabled = 2)
	// TODO: Should use the #define ADC_CHANNELS
	ADC1->SQR1 |= ADC_SQR1_L_1; // ADC_SQR1_L_1 = 2 channels
	ADC1->JSQR = 0;	// No injected group

	//The Temperature sensor is connected to channel ADCx_IN16 and the internal reference
	//voltage VREFINT is connected to ADCx_IN17. These two internal channels can be selected
	//and converted as injected or regular channels.
	// Enable VREF
	ADC1->CR2 |= ADC_CR2_TSVREFE;

	// Enable SCAN mode
	ADC1->CR1 |= ADC_CR1_SCAN;

	// Enable DMA
	ADC1->CR2 |= ADC_CR2_DMA;

	// Enable continuous conversion mode, i.e. no need to re-trigger
	// TODO: Does not probably allow consistent data readout if interrupt does not work
	//ADC1->CR2 |= ADC_CR2_CONT;

	// Enable ADC (turn on from sleep mode)
	ADC1->CR2 |= ADC_CR2_ADON;


	// Clear ADC calibration
	ADC1->CR2 |= ADC_CR2_RSTCAL;
	while(ADC1->CR2 & ADC_CR2_RSTCAL);

	// Calibrate the ADC during init
	ADC1->CR2 |= ADC_CR2_CAL;
	while(ADC1->CR2 & ADC_CR2_CAL);	// Wait until calibration is done


	// Configure and enable DMA
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	// Configure DMA channel 1 transfers before enabling the channel

	// Select number of data to transfer
	DMA1_Channel1->CNDTR = ADC_CHANNELS & 0xFFFF;
	// Peripheral address
	DMA1_Channel1->CPAR = &(ADC1->DR);
	// Memory address
	DMA1_Channel1->CMAR = &adc_results[0];


	// Use channel 1 for ADC1 transfer
	// Set word size to 16 bits
	DMA1_Channel1->CCR |= DMA_CCR1_MSIZE_0 | DMA_CCR1_PSIZE_0 |
			DMA_CCR1_MINC |	// Increment memory address
			DMA_CCR1_TCIE;	// Transfer complete interrupt

	DMA1_Channel1->CCR |= DMA_CCR1_EN;	// Enable channel

	// ADC will automatically trigger the DMA transfer
	// the trigger does not need to be configured in DMA

	// Enable ADC interrupt
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);

	// Trigger first ADC conversion
	ADC1->CR2 |= ADC_CR2_ADON;
}

signed char temperature_internal(void)
{
	return int_temp;
}

signed char temperature_out(void)
{
	// TODO: RF module temperature seems to be quite close
	// to external temperature se let's use that one
	return rf_get_temperature();
}

unsigned char supply_voltage(void)
{
	if(v_supply > 5100)
		return 0xFF;		// 255 = 5.1 V
	return v_supply / 20;
}

// Temperature sensor voltage at 25 C = 1.4 V
static unsigned short v_25 = 1400;

// Temperature sensor slope 4.3 mV/C ==> 233 C / V
static unsigned short c_per_v = 233;

void temperature_read(void)
{
	float temp;
	unsigned short offset;
	signed short temperature;

	// Check if conversion is finished
	if(!(ADC1->SR & ADC_SR_EOC)) return;

	// Check if DMA transfer is finished
	//if(!(DMA1->ISR & DMA_ISR_TCIF1)) return;

	// Check the flag
	if(!dma_trigs)
		return;
	dma_trigs = 0;

	// Calculate supply voltage (used as ADC ref+) from 2nd
	// ADC measurement, which is the internal 1.2 V reference
	// 49140 = 1000 * 4095 * 1.2, i.e. v_supply = (4095/adc_result) * 1.2 * 1000
	v_supply = 4914000 / adc_results[1];

	// Convert the offset at 25C to ADC units
	temp = (float)v_25 / v_supply;
	offset = temp * 4095;

	// Convert the slope to celsius/ADC unit
	temp = (float)v_supply / 1000.0;
	temp = (float)c_per_v * temp / 4095;

	// Update temperature reading (1st ADC measurement)
	// At 25 C the reading is about 1.4 V (1.34 ... 1.52)
	// And slope is about 4.3 mV/C (4 ... 4.6)
	// V_sensor = adc_result/4095 * v_supply
	// TODO: Below is wrong
	// temp = 25 + (V_sensor - 1.4) * 0.0043 (using the default values)
	// This is right:
	// Temp = (V25 - V_sensor) / slope + 25C

	// Subtract offset
	//temperature = adc_results[0] - offset;
	temperature = offset - adc_results[0];

	// Multiply by the volts/celsius value
	int_temp = (float)(temperature) * temp;

	int_temp += 25;

	// Clear flags
	ADC1->SR &= ~(ADC_SR_STRT | ADC_SR_EOC);
	DMA1->IFCR |= DMA_IFCR_CTCIF1;

	// Start next ADC conversion
	ADC1->CR2 |= ADC_CR2_ADON;
}



void DMA1_Channel1_IRQHandler(void)
{
	// Toimii!
	++dma_trigs;

	// Clear interrupt flags
	ADC1->SR &= ~(ADC_SR_STRT | ADC_SR_EOC);
	DMA1->IFCR |= DMA_IFCR_CTCIF1;

	return; // TODO: This takes all the processor time at the moment...
}
