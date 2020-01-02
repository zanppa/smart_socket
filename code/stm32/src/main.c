/*
 * Smart remote socket main function
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

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "cmsis/system_stm32f10x.h"

#include "Timer.h"
#include "RelayControl.h"
#include "Scheduler.h"
#include "Button.h"
#include "Temperature.h"
#include "RfApi.h"

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

// Read RF module temperature every 30 seconds
#define RF_TEMPERATURE_INTERVAL		(30000)


int main(int argc, char* argv[])
{
	uint8_t buttons_pressed = 0, button_state = 0, prev_button_state = 0;
	uint8_t relays = 0;
	uint16_t read_temp_timer = RF_TEMPERATURE_INTERVAL;
	ledMode_t led1_mode = led_off, led2_mode = led_off;

	// These are called from elsewhere (_start)
	//SystemInit();
	//SystemCoreClockUpdate();

	// TODO: Testing testing...
	/*
    RCC->CR |=RCC_CR_HSEON;
    while(!(RCC->CR & RCC_CR_HSERDY)); // wait until external crystal osc is ready
    while((RCC->CR & RCC_CR_PLLRDY)==0);     // wait for clock to settle
     RCC->CFGR |= 2;                          // set PLL used as system clock
     while((RCC->CFGR & RCC_CFGR_SWS_1)==0); // switch to pll
*/

	//__enable_irq();

	//NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x08008000);

	// RTC must be started up first since it may
	// reset backup domain etc to change the RTC clock source
	RTC_init();

	// Enable system tick to run every 1 ms
	timer_init();

	// Enable other subsystems

	relay_control_init();
	button_init();
	led_init();
	temperature_init();

	scheduler_init();

	// Initialize radio
	//SX1278_HWMainInit();
	rf_init();

	// Read the internal temperature
	temperature_read();

	// Read the radio module temperature
	rf_read_temperature();

	// Infinite loop
	while (1)
	{
		// Wait for system tick to pass
		if(systick_trigd)
		{
			systick_trigd = 0;

			RTC_update();
			scheduler_update();
			rf_update();

			// Read temperature sensors, maybe
			if(read_temp_timer)
				read_temp_timer--;
			else
			{
				read_temp_timer = RF_TEMPERATURE_INTERVAL;
				temperature_read();
				rf_read_temperature();
			}

			// Read button presses
			button_update();
			prev_button_state = button_state;
			button_state = button_state_get();

			// Make variable 1 only if button was just pressed down
			// otherwise zero
			buttons_pressed = button_state & (button_state ^ prev_button_state);

			// Change relay states if buttons are pressed
			// Always overrides timers
			if(buttons_pressed & 0x1)
			{
				relay_control_toggle(0);
				//rf_transmit("T\0\0", 2, 2000);
			}

			if(buttons_pressed & 0x2)
			{
				relay_control_toggle(1);
			}

			// Update relay functions (pending requests etc)
			relay_update();

			// Read relay states
			relays = relay_get_states();

			// Store latest state info to backup register 2
			// to be able to restore after power out
			BKP->DR2 = relays;

			// First indicator LED for first relay
			if(relays & 0x10)
				led1_mode = led_long_blink;
			else if(relays & 0x1)
				led1_mode = led_constant;
			else
				led1_mode = led_off;

			// Second LED for second relay
			if(relays & 0x20)
				led2_mode = led_long_blink;
			else if(relays & 0x2)
				led2_mode = led_constant;
			else
				led2_mode = led_off;

			led_toggle(led1_mode, led2_mode);
		}
	}
}

#pragma GCC diagnostic pop
