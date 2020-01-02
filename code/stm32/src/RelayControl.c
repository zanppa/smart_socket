/*
 * Smart remote socket relay control functions
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

#include "RelayControl.h"
#include "Timer.h"

// Relay state
// TODO: Change to bit mask
static uint8_t relay_state[2];

// Is relay turn-on request pending?
// TODO: Change to bit mask
static uint8_t relay_request[2];

// Delayed relay command, to be applied at update
static uint8_t relay_command[2];

void relay_control_init()
{
	// Enable GPIO Peripheral clock
	// TODO: Check if this resets anything?
	RCC_APB2PeriphClockCmd(RELAY_RCC_MASKx(RELAY_PORT_NUMBER), ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	// Configure pin in output push/pull mode
	GPIO_InitStructure.GPIO_Pin = RELAY_PIN_MASK(RELAY1_PIN_NUMBER) | RELAY_PIN_MASK(RELAY2_PIN_NUMBER);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(RELAY_GPIOx(RELAY_PORT_NUMBER), &GPIO_InitStructure);

	// Use hardware timers for controlling the turn-on/off times
	// TIM4 and TIM5 general purpose timers
	// Timer 5 for first relay
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM4->CR1 = TIM_CR1_DIR | TIM_CR1_OPM;	// Count down in one-pulse mode
	TIM4->PSC = 36000;		// From 72 MHz to 2 kHz
	TIM4->ARR = RELAY_DELAY_TIME*2;	// Preload timer value
	TIM4->CNT = RELAY_DELAY_TIME*2;
	TIM4->SR = 0;			// Clear interrupt flags

	// Timer 5 for second relay
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	TIM5->CR1 = TIM_CR1_DIR | TIM_CR1_OPM;	// Count down in one-pulse mode
	TIM5->PSC = 36000;		// From 72 MHz to 10 kHz
	TIM5->ARR = RELAY_DELAY_TIME*2;	// Preload timer value
	TIM5->CNT = RELAY_DELAY_TIME*2;
	TIM5->SR = 0;			// Clear interrupt flags

	// Start with relay states off
	relay_state[0] = 0;
	relay_state[1] = 0;
	relay_request[0] = 0;
	relay_request[1] = 0;
	relay_command[0] = 0;
	relay_command[1] = 0;
}


// Return 0 if relay control is delayed and cannot be turned on
uint8_t relay_control_on(unsigned char relay)
{
	relay = relay ? 1 : 0;

	// Turn I/O pin
	if(relay)
	{
		// Second relay
		// Check if delay timer is running, if it is, prevent turn-on
		if(TIM5->CR1 & TIM_CR1_CEN)
		{
			relay_request[relay] = 1;
			return 0;
		}

		relay_command[relay] = 1;
	}
	else
	{
		// First relay
		// Check if delay timer is running, if it is, prevent turn-on
		if(TIM4->CR1 & TIM_CR1_CEN)
		{
			relay_request[relay] = 1;
			return 0;
		}
	}

	// Mark the relay as turned on
	relay_request[relay] = 0;
	relay_command[relay] = 1;
	return 1;
}

uint8_t relay_control_off(unsigned char relay)
{
	relay = relay ? 1 : 0;

	// Turn I/O pin
	if(relay)
	{
		// Second relay

		// Trigger the timer if was not pending already
		if(!relay_request[relay])
			TIM5->CR1 |= TIM_CR1_CEN;
	}
	else
	{
		// First relay

		// Trigger the timer
		if(!relay_request[relay])
			TIM4->CR1 |= TIM_CR1_CEN;
	}

	// Mark the state that the relay is off
	relay_state[relay] = 0;
	relay_request[relay] = 0;
	relay_command[relay] = 0;

	return 1;
}

// Update relays, i.e. delayed turn-on
void relay_update(void)
{
	uint8_t relay;

	for(relay = 0; relay < 2; relay++)
	{
		// If relay control has pending request, try to turn on
		if(relay_request[relay])
			relay_control_on(relay);
	}

	if(relay_command[0]) {
		GPIO_SetBits(RELAY_GPIOx(RELAY_PORT_NUMBER), RELAY_PIN_MASK(RELAY1_PIN_NUMBER));
		relay_state[0] = 1;
	} else {
		GPIO_ResetBits(RELAY_GPIOx(RELAY_PORT_NUMBER), RELAY_PIN_MASK(RELAY1_PIN_NUMBER));
		relay_state[0] = 0;
	}

	if(relay_command[1]) {
		GPIO_SetBits(RELAY_GPIOx(RELAY_PORT_NUMBER), RELAY_PIN_MASK(RELAY2_PIN_NUMBER));
		relay_state[1] = 1;
	} else {
		GPIO_ResetBits(RELAY_GPIOx(RELAY_PORT_NUMBER), RELAY_PIN_MASK(RELAY2_PIN_NUMBER));
		relay_state[1] = 0;
	}
}

uint8_t relay_control_toggle(unsigned char relay)
{
	if(relay_get_state(relay) || relay_is_delayed(relay))
		return relay_control_off(relay);
	else
		return relay_control_on(relay);
}

uint8_t relay_get_state(unsigned char relay)
{
	return relay_state[relay ? 1 : 0];
}

uint8_t relay_is_delayed(unsigned char relay)
{
	return relay_request[relay ? 1 : 0];
}

// Get state of both relays
// Bits 0 and 1 indicate state, on or off
// bits 4 and 5 indicate if relay state is delayed, i.e. waiting
uint8_t relay_get_states(void)
{
	uint8_t ret = (relay_get_state(0) ? 0x1 : 0) | (relay_get_state(1) ? 0x2 : 0);
	ret |= (relay_is_delayed(0) ? 0x10 : 0) | (relay_is_delayed(1) ? 0x20 : 0);
	return ret;
}
