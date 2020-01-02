/*
 * Smart remote socket button and led header
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
 
#ifndef BUTTON_H_
#define BUTTON_H_

#include "stm32f10x.h"

// Debounce time in 100 us (timer runs at 10 kHz)
#define BUTTON_DEBOUNCE_TIME				(5000)		// 500 ms

// LED blink period, timer also runs at 10 kHz
#define LED_BLINK_PERIOD				(0x2000)	// About 0.82 seconds
#define LONG_BLINK_MASK					(0x1000)	// About 0.41 seconds
#define SHORT_BLINK_MASK				(0x800)		// About 0.2 seconds

typedef enum _ledMode_t {
		led_off = 0,
		led_constant = 1,
		led_short_blink,
		led_long_blink
} ledMode_t;

// Relay control definition
// Port number: 0=A, 1=B, 2=C, 3=D, 4=E, 5=F, 6=G, ...
#define BUTTON1_PIN_NUMBER				(13)
#define BUTTON1_PIN_MASK				(GPIO_Pin_13)
#define BUTTON2_PIN_NUMBER				(14)
#define BUTTON2_PIN_MASK				(GPIO_Pin_14)

#define BUTTON_GPIO                 	((GPIO_TypeDef *)GPIOB_BASE)
#define BUTTON_RCC_MASK             	(RCC_APB2Periph_GPIOB)

#define LED1_PIN_NUMBER					(11)
#define LED1_PIN_MASK					(1 << LED1_PIN_NUMBER)

#define LED2_PIN_NUMBER					(12)
#define LED2_PIN_MASK					(1 << LED2_PIN_NUMBER)

#define LED_GPIO                	 	((GPIO_TypeDef *)GPIOB_BASE)
#define LED_RCC_MASK             		(RCC_APB2Periph_GPIOB)


extern void button_init(void);
extern void led_init(void);

// Update button status
extern void button_update(void);

// Get the current button state
extern uint8_t button_state_get(void);

extern void led_toggle(ledMode_t led1_mode, ledMode_t led2_mode);

#endif // BUTTON_H_
