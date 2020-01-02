/*
 * Smart remote socket relay control header
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

#ifndef RELAYCONTROL_H_
#define RELAYCONTROL_H_

#include "stm32f10x.h"

// Only allow turn-on event after 30 seconds of last turn-on (value in ms)
// Maximum time is 65535 / 2 = about 32 seconds
// because the timer is 16 bit and runs at 2 kHz
#define RELAY_DELAY_TIME				(30000)


// Relay control definition
// Port number: 0=A, 1=B, 2=C, 3=D, 4=E, 5=F, 6=G, ...
#define RELAY_PORT_NUMBER               (1)
#define RELAY1_PIN_NUMBER          		(1)
#define RELAY2_PIN_NUMBER				(2)

#define RELAY_GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define RELAY_PIN_MASK(_N)              (1 << (_N))
#define RELAY_RCC_MASKx(_N)             (RCC_APB2Periph_GPIOA << (_N))

extern void relay_control_init(void);

// Turn relay on. Returns 1 on success, 0 if relay is turned on too often and is delayed
extern uint8_t relay_control_on(unsigned char relay);

// Turn relay off, return 1 on success, 0 otherwise
extern uint8_t relay_control_off(unsigned char relay);

extern uint8_t relay_control_toggle(unsigned char relay);

// Returns 0 if relay is controllable, 1 if relay needs to wait until next event
extern uint8_t relay_is_delayed(unsigned char relay);

extern uint8_t relay_get_state(unsigned char relay);

// Get state of both relays
extern uint8_t relay_get_states(void);

// Update relays, i.e. delayed turn-on
extern void relay_update(void);

#endif // RELAYCONTROL_H_
