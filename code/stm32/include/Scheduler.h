/*
 * Smart remote socket scheduler header
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

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "stm32f10x.h"

// TODO: Make these configurable, i.e. read from config class when that is done
#define TEMPERATURE_OFFSET		(15*60)		// 15 minutes additional heating time (after "leaving" time)
#define TEMPERATURE_GAIN		(-12*60)		// 12 minutes / degree C below 0 degrees
#define TEMPERATURE_MIN_TIME	(30*60)			// Minimum 30 minutes of heating
#define TEMPERATURE_MAX_TIME	(180*60)		// Max 3 hours of warm-up time
#define TEMPERATURE_LIMIT		(0)		// Only heat below 0 degrees

typedef uint8_t schedMode_t;
#define SCHED_MODE_OFF			(0x00)
#define SCHED_MODE_ON			(0x01)
#define SCHED_REPEAT_DAILY		(0x02)
#define SCHED_REPEAT_WEEKLY		(0x04)
#define SCHED_RESERVED1			(0x08)
#define SCHED_RESERVED2			(0x10)
#define SCHED_RELAY2			(0x20)		// Control the second relay instead of first
#define SCHED_USE_TEMPERATURE	(0x40)		// Turn-off time is leave time, use temperature to set turn-on. Should only be used for turn-on, where time is the leave time
#define SCHED_MODE_BLOCK_ONCE	(0x80)		// Blocks the next event, then continues

#define SCHED_BKP_START		(&(BKP->DR13))

#define SCHED_MAX_EVENTS		(16)
#define SCHED_STORE_EVENTS		(10)
#define SCHED_NO_EVENT_TIME		(0)
#define SCHED_NO_EVENT			(0xFF)
typedef uint8_t schedID_t;
typedef struct _schedEvent {
	uint32_t time;
	schedMode_t mode;
	uint8_t pad[3];		// Padding to make struct 4 aligned, not used
} schedEvent_t;

extern void scheduler_init(void);

// Update timer etc.
extern void scheduler_update(void);

extern void scheduler_clear(void);

// Add new scheduled event, returns id of the event
extern schedID_t scheduler_add(uint32_t time, schedMode_t mode);

// Remove scheduled event with id. Return 1 if success
extern uint8_t scheduler_remove(schedID_t id);

// Block the next call to event with id. Returns 1 on success
extern uint8_t scheduler_block(schedID_t id);

// Unbock the next call to event with id. Returns 1 on success
extern uint8_t scheduler_unblock(uint8_t id);

// Set start of daylight savings time. Does not repeat, must be re-programmed yearly
extern uint8_t scheduler_dst_begin(uint32_t time, uint32_t offset);

// Set the end of DST. Does not repeat, must be re-programmed yearly
extern uint8_t scheduler_dst_end(uint32_t time, uint32_t offset);

// Finish changes etc. and start the scheduler
extern uint8_t scheduler_finish(void);

// Return event type
schedMode_t scheduler_event_type(schedID_t id);

// Return event time
uint32_t scheduler_event_time(schedID_t id);

#endif // SCHEDULER_H_
