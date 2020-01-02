/*
 * Smart remote socket timer and RTC functions
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

#include "Timer.h"
#include "cortexm/ExceptionHandlers.h"


#if defined(USE_HAL_DRIVER)
void HAL_IncTick(void);
#endif

// Forward declarations of functions
void timer_tick (void);

// Timer variables
static volatile timer_ticks_t timer_delay[DELAY_TIMERS] = {0};
static volatile timer_ticks_t timer_loop[LOOP_TIMERS] = {0};
static volatile timer_ticks_t timer_loop_setup[LOOP_TIMERS] = {0};
static volatile timer_n_t timer_delay_trig = 0;
static volatile timer_n_t timer_loop_trig = 0;

volatile uint8_t systick_trigd = 0;
static volatile uint8_t RTC_trigd = 0;
static volatile uint8_t RTC_alm_trigd = 0;

volatile uint16_t rfTimer = 0;

void timer_init (void)
{
	timer_n_t timer;

	systick_trigd = 0;
	RTC_trigd = 0;

	// Reset all timers etc to zero
	timer_delay_trig = 0u;
	timer_loop_trig = 0u;

	for(timer = 0; timer < DELAY_TIMERS; timer++)
		timer_delay[timer] = 0u;

	for(timer = 0; timer < LOOP_TIMERS; timer++)
	{
		timer_loop[timer] = 0u;
		timer_loop_setup[timer] = 0u;
	}

	// Use SysTick as reference for the delay loops.

	// Configure system tick clock to be main processor clock / 8
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);

	// Configure system tick timer
    SysTick->CTRL = 0;
    SysTick->LOAD = SystemCoreClock / ( 8 * TIMER_FREQUENCY_HZ) - 1;
    SysTick->VAL = 0; // Load the SysTick Counter Value
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk;

    //SysTick_Config (SystemCoreClock / TIMER_FREQUENCY_HZ);

    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    //NVIC_SetPriority(SysTick_IRQn, 0);
}

void timer_setup_delay(timer_n_t timer, timer_ticks_t value)
{
	if(timer >= DELAY_TIMERS) return;
	timer_delay[timer] = value;
	timer_delay_trig &= (timer_n_t)(~(1 << timer));
}

void timer_setup_loop(timer_n_t timer, timer_ticks_t value)
{
	if(timer >= LOOP_TIMERS) return;
	timer_loop_setup[timer] = value;
	timer_loop[timer] = value;
	timer_loop_trig &= (timer_n_t)(~(1 << timer));
}

uint8_t timer_trigd_delay(timer_n_t timer, uint8_t reset)
{
	timer_n_t trigd;

	if(timer >= DELAY_TIMERS) return 0;
	trigd = timer_delay_trig & (1 << timer);
	if(reset)
		timer_delay_trig &= (timer_n_t)(~trigd);

	return trigd ? 1 : 0;
}

uint8_t timer_trigd_loop(timer_n_t timer, uint8_t reset)
{
	timer_n_t trigd;
	if(timer >= LOOP_TIMERS) return 0;

	trigd = timer_loop_trig & (timer_n_t)(1 << timer);
	if(reset)
		timer_loop_trig &= (timer_n_t)(~trigd);

	return trigd ? 1 :0;
}

timer_ticks_t timer_get_delay_value(timer_n_t timer)
{
	if(timer >= DELAY_TIMERS) return 0;
	return timer_delay[timer];
}

timer_ticks_t timer_get_loop_value(timer_n_t timer)
{
	if(timer >= LOOP_TIMERS) return 0;
	return timer_loop[timer];
}


void timer_tick(void)
{
	timer_n_t timer;

	systick_trigd = 1;

	if(rfTimer) --rfTimer;

	// Decrement all delay timers
	for(timer = 0; timer < DELAY_TIMERS; timer++)
	{
		if(timer_delay[timer] != 0u)
			--timer_delay[timer];

		// Check if reached zero -> turn trig-bit 1
		if(!timer_delay[timer])
			timer_delay_trig |= (timer_n_t)(1 << timer);
	}

	// Decrement all loop timers
	for(timer = 0; timer < LOOP_TIMERS; timer++)
	{
		if(timer_loop[timer] != 0u)
			--timer_loop[timer];

		// Check if reached zero -> turn trig-bit 1 and loop
		if(!timer_loop[timer])
		{
			timer_loop_trig |= (timer_n_t)(1 << timer);
			timer_loop[timer] = timer_loop_setup[timer];
		}
	}
}

void SysTick_Handler(void)
{
	timer_tick();
}


// RTC

// RTC variables

static uint32_t RTC_current_time_value;
static volatile uint32_t RTC_alarm_time_value;


// Enter RTC configuration mode
void RTC_enter_config(void)
{
	while(!(RTC->CRL & RTC_CRL_RTOFF));		// Wait until ready
	RTC->CRL |= RTC_CRL_CNF;				// Enter config mode
}

// Leave RTC configuration mode
void RTC_leave_config(void)
{
	RTC->CRL &= ~RTC_CRL_CNF;				// Leave config mode
	while(!(RTC->CRL & RTC_CRL_RTOFF)); 	// Wait until ready
}


// Initialize the RTC
void RTC_init(void)
{
	uint16_t startup_timeout = 0;

	// Preset values
	RTC_current_time_value = 0;
	RTC_alarm_time_value = 0;

	// TODO: Does this work properly if backup VBAT is used??

	// Enable power interface clock
	RCC->APB1ENR |= RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN;

	// Enable access to RTC and backup registers
	PWR->CR |= PWR_CR_DBP;

	// Enable RTC interrupt (early)
	NVIC_EnableIRQ(RTC_IRQn);
	//NVIC_EnableIRQ(RTCAlarm_IRQn); // This seems to not be needed in this application


	// Check if RTC is already configured and running (from backup power)
	// and do not do anything if it is...
	// Use backup data register 1 for RTC configuration (reset value is 0).
	if(BKP->DR1 & 0x0001) return;

	// Device was hard reset, so continue configuring the RTC

	// Reset Backup Domain Config
	RCC->BDCR |= RCC_BDCR_BDRST;
	RCC->BDCR &= ~RCC_BDCR_BDRST;

	// Start LSE clock
	RCC->BDCR |= RCC_BDCR_LSEON;

	// Wait until LSE is ready
	while ( !(RCC->BDCR & RCC_BDCR_LSERDY) && (++startup_timeout) != RTC_LSE_STARTUP_TIME);

	// Check if LSE startup was successful
	if(RCC->BDCR & RCC_BDCR_LSERDY)
	{
		// Select LSE as RTC clock source
		RCC->BDCR |= RCC_BDCR_RTCSEL_LSE;

		// Enable RTC clock
		RCC->BDCR |= RCC_BDCR_RTCEN;

		// Set RTC prescaler to 32768
		RTC_enter_config();
		// 32 768 - 1 in hex is 0x7FFF
		RTC->PRLL = 0x7FFF;
		RTC_leave_config();
	}
	else
	{
		// Stop trying to start the LSE clock
		RCC->BDCR &= ~RCC_BDCR_LSEON;

		// Use high speed clock crystal as RTC source
		// RTCSETL = 11 => use HCI / 128 as the RTC clock source
		RCC->BDCR |= RCC_BDCR_RTCSEL_HSE;

		// Enable RTC clock
		// TODO: Must be done before clock prescaler can be set??
		RCC->BDCR |= RCC_BDCR_RTCEN;

		// Set RTC parameters
		RTC_enter_config();
		// Clock is 8 MHz divided by 128, i.e. prescaler is 62 500 - 1
		// In hex 0xF423
		RTC->PRLL = 0xF423;
		RTC_leave_config();
	}

	// Set some default time since the clock has been reset
	RTC_set_time(RTC_DEFAULT_TIME);
	//RTC_set_alarm(RTC_DEFAULT_TIME + 30);

	// Enable RTC second interrupt
	RTC->CRH |= RTC_CRH_SECIE;

	// Write 1 to backup data register 1 to indicate the RTC has been configured
	BKP->DR1 = 0x0001;
}

void RTC_update(void)
{
	if(RTC_trigd)
	{
		RTC_trigd = 0;

		// Read the current time value and store to variable
		RTC_get_time();
	}
}

// Set current time of day
void RTC_set_time(uint32_t seconds)
{
	RTC_enter_config();

	// Set the time in seconds
	RTC->CNTL = (uint16_t)(seconds & 0xFFFF);
	RTC->CNTH = (uint16_t)((seconds >> 16) & 0xFFFF);

	RTC_leave_config();

	// Instant update value, without reading the registers back
	RTC_current_time_value = seconds;
}

// Get current time in seconds, read directly from register, and store to variable
uint32_t RTC_get_time(void)
{
	uint16_t rtc_h, rtc_l;
	uint16_t rtc_h2, rtc_l2;
	uint32_t ret;

	rtc_h = RTC->CNTH;
	rtc_l = RTC->CNTL;

	// Read twice to check for overflow between reads
	rtc_h2 = RTC->CNTH;
	rtc_l2 = RTC->CNTL;

	// Check overflow
	if(rtc_h2 == rtc_h) // No overflow
		ret = (rtc_h << 16) + rtc_l;
	else	// Overflow, use the later ones
		ret = (rtc_h2 << 16) + rtc_l2;

	RTC_current_time_value = ret;
	return ret;
}

// Set alarm
void RTC_set_alarm(uint32_t seconds)
{
	RTC_enter_config();

	// Set alarm register value
	RTC->ALRL = seconds & 0xFFFF;
	RTC->ALRH = (seconds >> 16) & 0xFFFF;

	RTC_leave_config();

	// Enable alarm interrupt, must be done outside RTC config mode
	RTC->CRH |= RTC_CRH_ALRIE;

	RTC_alarm_time_value = seconds;
}

uint8_t RTC_alarm_trigd(uint8_t reset)
{
	uint8_t ret = RTC_alm_trigd;

	if(reset)
		RTC_alm_trigd = 0;

	return ret;
}

// Get current time
uint32_t RTC_current_time(void)
{
	return RTC_current_time_value;
}


void RTC_IRQHandler(void)
{
	// Called every second

	// Check the interrupt source
	if (RTC->CRL & RTC_CRL_SECF)
	{
		// RTC second interrupt

		// Clear it
		RTC->CRL &= ~RTC_CRL_SECF;
		RTC_trigd = 1;
	}

	if(RTC->CRL & RTC_CRL_ALRF)
	{
		// RTC alarm interrupt

		// Clear the flag
		RTC->CRL &= ~RTC_CRL_ALRF;
		RTC_alm_trigd = 1;

	}

	if(RTC->CRL & RTC_CRL_OWF)
	{
		// Timer overflow interrupt
		// Clear the flag
		RTC->CRL &= ~RTC_CRL_OWF;
	}
}
