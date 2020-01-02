/*
 * Smart remote socket timer and RTC header
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

#ifndef TIMER_H_
#define TIMER_H_

#include "cmsis_device.h"

#define TIMER_FREQUENCY_HZ	(1000u)

// Amount of timers must be less than the word size of timer_t
#define DELAY_TIMERS		(8)
#define LOOP_TIMERS			(8)

typedef uint32_t timer_ticks_t;
typedef uint8_t timer_n_t;

// Systick trigger to be used in main loop
extern volatile uint8_t systick_trigd;

extern volatile uint16_t rfTimer;

// Generic timer functions

// Calling this function resets and starts all the timers
extern void timer_init(void);
void timer_tick(void);

extern void timer_setup_delay(timer_n_t timer, timer_ticks_t value);

// Set value to 0 to disable looping timer
extern void timer_setup_loop(timer_n_t timer, timer_ticks_t value);

// Return 1 if timer has triggered (reached zero). Set reset to 1 to also reset the value
extern uint8_t timer_trigd_delay(timer_n_t timer, uint8_t reset);
extern uint8_t timer_trigd_loop(timer_n_t timer, uint8_t reset);

// Get timer current value(s)
extern timer_ticks_t timer_get_delay_value(timer_n_t timer);
extern timer_ticks_t timer_get_loop_value(timer_n_t timer);


// RTC (real-time clock) functions

// 1541965200 is unix time for 11.11.2018 21:40:00 (UTC+2)
#define RTC_DEFAULT_TIME		(1541965200)

// Timeout when trying to start the low-speed oscillator
#define RTC_LSE_STARTUP_TIME	(0x1000)


// Initialize the RTC
extern void RTC_init(void);

// Synchronized update of parameters
extern void RTC_update(void);

// Set current time in seconds since epoch
extern void RTC_set_time(uint32_t seconds);

// Get current time in seconds since epoch, read directly from register, and store to variable
extern uint32_t RTC_get_time(void);

// Get current time stored in the variable
extern uint32_t RTC_current_time(void);

// Set next alarm in seconds since epoch
extern void RTC_set_alarm(uint32_t seconds);

// Check whether the rTC alarm has been triggered, and reset if set to true
extern uint8_t RTC_alarm_trigd(uint8_t reset);

#endif // TIMER_H_
