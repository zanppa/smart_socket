/*
 * Smart remote socket scheduler functions
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

#include "Scheduler.h"
#include "Relaycontrol.h"
#include "Timer.h"
#include "Temperature.h"

static signed char temperature = 99;
static uint32_t temperature_heating_time = 0;

// Forward declarations
void scheduler_update_events(uint32_t current_time);
void scheduler_calculate_temperature(void);
uint32_t scheduler_event_alarm_time(schedID_t id, uint32_t current_time);
void scheduler_set_next_alarm(uint32_t current_time);

// Event table
static schedEvent_t events[SCHED_MAX_EVENTS];
schedID_t next_event;

void scheduler_init(void)
{
	uint8_t i;
	uint16_t *addr = SCHED_BKP_START;

	scheduler_clear();

	// Read events from data registers if DR1 != 0
	if(BKP->DR1)
	{
		next_event = BKP->DR3;

		for(i=0;i<SCHED_STORE_EVENTS && i<SCHED_MAX_EVENTS;i++)
		{
			events[i].time = *addr;
			addr += 4;
			events[i].time |= (*addr) << 16;
			addr += 4;
			events[i].mode = *addr;
			addr +=4;
		}

		// Call finish to make sure all passed events
		// are cleared and the alarm is set correctly.
		scheduler_finish();
	}
}

// Update timer etc.
void scheduler_update(void)
{
	schedID_t id;
	uint32_t current_time = (uint32_t)~0;

	// Update temperature and pre-heating time
	// Done here so that RF status can also see the value(s)
	scheduler_calculate_temperature();

	// Check if RTC alarm has trig'd
	// i.e. time to an event has passed
	if(RTC_alarm_trigd(1))	// Clear the alarm flag
	{
		current_time = RTC_current_time();

		// Loop through all items that are currently ongoing
		for(id = 0; id < SCHED_MAX_EVENTS; id++)
		{
			if(events[id].time == SCHED_NO_EVENT_TIME)
				continue;

			// If event time has passed -> it should be activated
			if(!(events[id].mode & SCHED_USE_TEMPERATURE) && events[id].time <= current_time)
			{
				if(events[id].mode & SCHED_MODE_BLOCK_ONCE)
				{
					// Event is blocked, clear the block and continue forward
					// doing nothing
					scheduler_unblock(id);
					continue;
				}

				if(events[id].mode & SCHED_MODE_ON)
				{
					// Turn on event, select which relay
					relay_control_on((events[id].mode & SCHED_RELAY2) ? 1 : 0);
				}
				else
				{
					// Turn-off, select correct relay
					relay_control_off((events[id].mode & SCHED_RELAY2) ? 1 : 0);
				}
			}

			// Temperature based turn-on
			// IF temperature is below the limit AND time exceeds the
			// pre-heating time
			else if((temperature < TEMPERATURE_LIMIT) &&
					(events[id].mode & SCHED_USE_TEMPERATURE) &&
					(events[id].time - temperature_heating_time) < current_time)
			{
				if(events[id].mode & SCHED_MODE_BLOCK_ONCE)
				{
					// Event is blocked, clear the block and continue forward
					// doing nothing
					// TODO: This does actually nothing sensible since it most likely will trig
					// on next update cycle anyways...
					scheduler_unblock(id);
					continue;
				}

				// Temperature mode, turn on at a time depending on temperature and then update the
				// event to turn off at the specified time
				if(events[id].mode & SCHED_MODE_ON)
				{
					// Turn on event, select which relay
					relay_control_on((events[id].mode & SCHED_RELAY2) ? 1 : 0);

					// Modify the event so that it is normal turn-off
					events[id].mode &= ~SCHED_MODE_ON;	// Clear turn on
					events[id].mode &= ~SCHED_USE_TEMPERATURE;
					events[id].mode |= SCHED_MODE_OFF;	// Set as turn-off
					events[id].time += TEMPERATURE_OFFSET;	// Add the offset in seconds
				}

				// TODO: Somehow needs to mark this as already activated or the
				// update will not remove or move it forward...?

			}
		}

		// Update events, e.g. recurring events and remove passed ones
		//scheduler_update_events();
		scheduler_finish();
	}
}

void scheduler_clear(void)
{
	schedID_t count;
	uint16_t *addr = SCHED_BKP_START;

	next_event = SCHED_NO_EVENT;

	// Clear events
	for(count = 0; count < SCHED_MAX_EVENTS; count++)
	{
		events[count].mode = 0;
		events[count].time = SCHED_NO_EVENT_TIME;
	}

	// TODO: Clear alarm
	RTC_set_alarm(0);

	// Clear backup registers
	BKP->DR3 = SCHED_NO_EVENT;

	for(count=0; count<SCHED_STORE_EVENTS && count<SCHED_MAX_EVENTS; count++)
	{
		*addr = 0;
		addr += 4;
		*addr = 0;
		addr += 4;
		*addr = 0;
		addr +=4;
	}
}

// Add new scheduled event, returns id of the event
schedID_t scheduler_add(uint32_t time, schedMode_t mode)
{
	schedID_t id = SCHED_NO_EVENT;
	schedID_t count;

	// Check if time has passed and no repetition flags, and bail out if it is
	if(time <= RTC_current_time() && !((mode & SCHED_REPEAT_DAILY) || (mode & SCHED_REPEAT_WEEKLY)))
		return SCHED_NO_EVENT;

	// Temperature based event can only be turn-on, which is the leaving time
	if((mode & SCHED_USE_TEMPERATURE) && !(mode & SCHED_MODE_ON))
		return SCHED_NO_EVENT;

	// Find first empty event and closest previous event
	for(count = 0; count < SCHED_MAX_EVENTS; count++)
	{
		// Find empty slot
		if(id == SCHED_NO_EVENT && events[count].time == SCHED_NO_EVENT_TIME)
			id = count;
	}

	// No free event slot found
	if(id == SCHED_MAX_EVENTS)
		return SCHED_NO_EVENT;

	// Fill the event struct
	events[id].mode = mode;
	events[id].time = time;

	if(next_event == SCHED_NO_EVENT)
		next_event = id;

	return id;
}

// Remove scheduled event with id. Return 1 if success
uint8_t scheduler_remove(uint8_t id)
{
	// Sanity check
	if(id >= SCHED_MAX_EVENTS || id == SCHED_NO_EVENT)
		return 0;

	events[id].mode = 0;
	events[id].time = SCHED_NO_EVENT_TIME;

	return 1;
}

// Block the next call to event with id. Returns 1 on success
uint8_t scheduler_block(uint8_t id)
{
	// Sanity check
	if(id >= SCHED_MAX_EVENTS)
		return 0;

	if(events[id].time == SCHED_NO_EVENT_TIME)
		return 0;

	events[id].mode |= SCHED_MODE_BLOCK_ONCE;
	return 1;
}

// Unbock the next call to event with id. Returns 1 on success
uint8_t scheduler_unblock(uint8_t id)
{
	// Sanity check
	if(id >= SCHED_MAX_EVENTS || id == SCHED_NO_EVENT)
		return 0;

	if(events[id].time == SCHED_NO_EVENT_TIME)
		return 0;

	events[id].mode &= (schedMode_t)~(SCHED_MODE_BLOCK_ONCE);
	return 1;
}

// Set start of daylight savings time. Does not repeat, must be re-programmed yearly
uint8_t scheduler_dst_begin(uint32_t time, uint32_t offset)
{
	return 0;
}

// Set the end of DST. Does not repeat, must be re-programmed yearly
uint8_t scheduler_dst_end(uint32_t time, uint32_t offset)
{
	return 0;
}

uint32_t scheduler_event_alarm_time(schedID_t id, uint32_t current_time)
{
	// Sanity check
	if(id >= SCHED_MAX_EVENTS || id == SCHED_NO_EVENT)
		return 0;

	uint32_t etime = events[id].time;
	if(etime == SCHED_NO_EVENT_TIME)
		return SCHED_NO_EVENT_TIME;

	if(events[id].mode & SCHED_USE_TEMPERATURE)
	{
		if(etime < (current_time + TEMPERATURE_MAX_TIME))	// If the max time has passed
			etime = current_time + 300;		// Check again in 5 minutes
		else	// Otherwise schedule as normal
			etime = etime - TEMPERATURE_MAX_TIME;
	}

	return etime + 1;	// Add one second so the event has really passed
}

void scheduler_update_events(uint32_t current_time)
{
	schedID_t id;
	uint32_t diff = (uint32_t)~0;
	uint32_t etimediff;
	next_event = SCHED_NO_EVENT;

	// Update all recurring events, and remove passed events
	for(id = 0; id < SCHED_MAX_EVENTS; id++)
	{
		if(events[id].time == SCHED_NO_EVENT_TIME)
			continue;	// Empty event slot

		while(events[id].time <= current_time)
		{
			if(events[id].mode & SCHED_REPEAT_DAILY)
			{
				// Move one day forward (24*60*60)
				events[id].time += 86400;
			}
			else if(events[id].mode & SCHED_REPEAT_WEEKLY)
			{
				// Move one week forward (7*24*60*60)
				events[id].time += 604800;
			}
			else
			{
				// Event has passed and no repetition -> delete
				scheduler_remove(id);
				break;
			}

			// TODO: Prevent infinite loop if counters wrap... i.e. time very much in future
		}

		// Re-check if event was removed
		if(events[id].time == SCHED_NO_EVENT_TIME)
			continue;

		// Find also the earliest event for RTC alarm
		etimediff = scheduler_event_alarm_time(id, current_time) - current_time;

		if(etimediff < diff)
		{
			diff = etimediff;
			next_event = id;
		}
	}
}

// Set RTC alarm to next alarm time
void scheduler_set_next_alarm(uint32_t current_time)
{
	RTC_set_alarm(scheduler_event_alarm_time(next_event, current_time));
}

// This should be called after adding/removing any events
uint8_t scheduler_finish(void)
{
	uint8_t i;
	uint16_t *addr = SCHED_BKP_START;

	uint32_t current_time = RTC_current_time();

	// Make sure everything is in mint condition
	scheduler_update_events(current_time);

	// Set alarm to next event, and then we wait...
	// Set alarm one second after the real time to make sure the time
	// has indeed passed and updated from registers
	scheduler_set_next_alarm(current_time);

	// Write events to backup registers
	BKP->DR3 = next_event;

	for(i=0;i<SCHED_STORE_EVENTS && i<SCHED_MAX_EVENTS;i++)
	{
		*addr = events[i].time & 0x0000FFFF;
		addr += 4;
		*addr = (events[i].time >> 16) & 0x0000FFFF;
		addr += 4;
		*addr = events[i].mode;
		addr +=4;
	}

	return 1;
}

schedMode_t scheduler_event_type(schedID_t id)
{
	if(id >= SCHED_MAX_EVENTS || id == SCHED_NO_EVENT)
		return 0;

	return events[id].mode;
}

uint32_t scheduler_event_time(schedID_t id)
{
	if(id >= SCHED_MAX_EVENTS || id == SCHED_NO_EVENT)
		return 0;

	return events[id].time;
}

// Calculate the pre-heating time based on external temperature
void scheduler_calculate_temperature(void)
{
	// Calculate heating time based on temperature
	// e.g. https://www.motiva.fi/ratkaisut/kestava_liikenne_ja_liikkuminen/nain_liikut_viisaasti/taloudellinen_ajaminen/moottorin_esilammitys

	temperature = temperature_out();

	if(temperature < TEMPERATURE_LIMIT)
	{
		// Both should be negative numbers
		temperature_heating_time = (uint32_t)(temperature_out()*TEMPERATURE_GAIN);

		if(temperature_heating_time > TEMPERATURE_MAX_TIME)
			temperature_heating_time = TEMPERATURE_MAX_TIME;
		else if(temperature_heating_time < TEMPERATURE_MIN_TIME)
			temperature_heating_time = TEMPERATURE_MIN_TIME;
	}
	else
	{
		temperature_heating_time = 0;
	}
}
