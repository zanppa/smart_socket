/*
 * Smart remote socket button handling functions
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

#include "Button.h"

void TIM3_IRQHandler(void);

static uint16_t button_state = 0;
static uint16_t led_state = 0;

// Initialize button GPIO and debounce timer 2
void button_init()
{
	RCC_APB2PeriphClockCmd(BUTTON_RCC_MASK, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	// Configure pins as inputs with pull-up
	GPIO_InitStructure.GPIO_Pin = BUTTON1_PIN_MASK | BUTTON2_PIN_MASK;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(BUTTON_GPIO, &GPIO_InitStructure);

	// Read and store initial GPIO state
	button_state = BUTTON_GPIO->IDR & (BUTTON1_PIN_MASK | BUTTON2_PIN_MASK);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	// Initialize timer 2 to be used as debounce
	// One shot count-down timer
	TIM2->CR1 = TIM_CR1_DIR | TIM_CR1_OPM;	// Count down in one-pulse mode
	TIM2->PSC = 7200;		// From 72 MHz to 10 kHz
	TIM2->ARR = BUTTON_DEBOUNCE_TIME;	// Preload timer value
	TIM2->CNT = BUTTON_DEBOUNCE_TIME;
	TIM2->SR = 0;			// Clear interrupt flags
}

// Initialize LEDs and timer 3 for LED blinking
void led_init()
{
	//RCC_APB2PeriphClockCmd(LED_RCC_MASK, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	// Configure pins as inputs with pull-up
	GPIO_InitStructure.GPIO_Pin = LED1_PIN_MASK | LED2_PIN_MASK;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LED_GPIO, &GPIO_InitStructure);


	// Enale clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	// Initialize timer 3 to be used as LEd blink timer
	TIM3->PSC = 7200;		// From 72 MHz to 10 kHz
	TIM3->ARR = LED_BLINK_PERIOD; // Preload timer value
	TIM3->CNT = 0;
	TIM3->SR = 0;			// Clear interrupt flags
	TIM3->DIER = TIM_DIER_UIE; // Enable update interrupt (timer level)
	TIM3->CR1 |= TIM_CR1_CEN;	// Enable timer

	// LEDs off
	led_state = 0;
	led_toggle(0, 0);
}


// Update button status
void button_update(void)
{
	uint16_t button_pins;

	// Read bits
	button_pins = BUTTON_GPIO->IDR & (BUTTON1_PIN_MASK | BUTTON2_PIN_MASK);

	// Check if button state has changed
	// and that timer 2 is disabled, i.e. debounce is not running
	// Next update is allowed after the debounce time
	if((button_pins != button_state) && !(TIM2->CR1 & TIM_CR1_CEN))
	{
		// Change button state
		button_state = button_pins;

		// Wait until bounce has stabilized, enable one-shot timer
		// The timer stops automatically and counters
		// return to the preload value
		TIM2->CR1 |= TIM_CR1_CEN;
	}
}

// Get the current button state
uint8_t button_state_get(void)
{
	// Buttons are active low, so bits are inverted
	return ((button_state & BUTTON1_PIN_MASK) ? 0 : 0x1) | ((button_state & BUTTON2_PIN_MASK) ? 0 : 0x2);
}

void led_toggle(ledMode_t led1_mode, ledMode_t led2_mode)
{
	if(led1_mode == led_constant ||
			(led1_mode == led_short_blink && (TIM3->CNT & SHORT_BLINK_MASK)) ||
			(led1_mode == led_long_blink && (TIM3->CNT & LONG_BLINK_MASK)))
		GPIO_SetBits(LED_GPIO, LED1_PIN_MASK);
	else
		GPIO_ResetBits(LED_GPIO, LED1_PIN_MASK);

	if(led2_mode == led_constant ||
			(led2_mode == led_short_blink && (TIM3->CNT & SHORT_BLINK_MASK)) ||
			(led2_mode == led_long_blink && (TIM3->CNT & LONG_BLINK_MASK)))
		GPIO_SetBits(LED_GPIO, LED2_PIN_MASK);
	else
		GPIO_ResetBits(LED_GPIO, LED2_PIN_MASK);
}

void TIM2_IRQHandler(void)
{
	;
}

void TIM3_IRQHandler(void)
{
	;
}
