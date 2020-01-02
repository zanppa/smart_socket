/*
 * Smart remote socket common RF API header
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

#ifndef RFAPI_H__
#define RFAPI_H__

#include "stm32f10x.h"

// Initialize SPI & GPIO hw, initialize LoRa module
void SX1278_HWMainInit(void);


// "common" api functions
void rf_init(void);  // Initialize everything
void rf_update(void);	// Update loop
uint8_t rf_mode_receive(uint16_t timeout);  // Switch to receive mode
uint8_t rf_available(void); // Returns number of bytes received
uint8_t rf_read(uint8_t *buffer, uint8_t len);  // Read bytes
uint8_t rf_transmit(uint8_t *buffer, uint8_t len, uint16_t timeout); // Transmit bytes
void rf_update_status(void);

void rf_read_temperature(void);
int8_t rf_get_temperature(void);	// Get the RF module temperature in C

#endif // RFAPI_H__
