/*
   database_dev.h

   Copyright(c) 2021 Michał Obrembski <michal.o@szerszen.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DATABASE_H
#define DATABASE_H

#include "database_types.h"
#include "callbacks.h"

#define MCP_COUNT_ON_I2C 4

typedef enum {
  SWITCH_1,
  SWITCH_2,
  SWITCH_3,
  SWITCH_4,
  SWITCH_5,
  SWITCH_6,
  SWITCH_7,
  SWITCH_OGROD,
  SWITCH_MAX_ID
} switchIds;

typedef enum {
  RELAY_1,
  RELAY_2,
  RELAY_3,
  RELAY_4,
  RELAY_5,
  RELAY_6,
  RELAY_7,
  RELAY_8,
  RELAY_MAX_ID
} relayIds;

static tLightSwitch m_lights[] =
{
    [SWITCH_1] =
    {
        .pin = 1,
        .description = "Switch1",
        .relayId = RELAY_1,
        .inactive = false,
        .i2cAddress = 0x20,
    },
    [SWITCH_2] =
    {
        .pin = 14,
        .description = "Switch2",
        .relayId = RELAY_2,
        .inactive = false,
        .i2cAddress = 0x20,
    },
    [SWITCH_3] =
    {
        .pin = 0,
        .description = "Switch3",
        .relayId = RELAY_3,
        .inactive = false,
        .i2cAddress = 0x20,
    },
    [SWITCH_4] =
    {
        .pin = 15,
        .description = "Switch4",
        .relayId = RELAY_4,
        .inactive = false,
        .i2cAddress = 0x20,
    },
    [SWITCH_5] =
    {
        .pin = 11,
        .description = "Switch5",
        .relayId = RELAY_5,
        .inactive = false,
    },
    [SWITCH_6] =
    {
        .pin = 10,
        .description = "Switch6",
        .relayId = RELAY_6,
        .inactive = false,
    },
    [SWITCH_7] =
    {
        .pin = 9,
        .description = "Switch7",
        .relayId = RELAY_7,
        .inactive = false,
    },
    [SWITCH_OGROD] =
    {
        .pin = 8,
        .description = "Switch8",
        .relayId = RELAY_8,
        .inactive = false,
    }
};

static tRelay m_relays[] =
{
    [RELAY_1] =
    {
        .pin = 7,
        .description = "Relay1",
        .i2cAddress = 0x20,
    },
    [RELAY_2] =
    {
        .pin = 8,
        .description = "Relay2",
        .i2cAddress = 0x20,
    },
    [RELAY_3] =
    {
        .pin = 6,
        .description = "Relay3",
        .i2cAddress = 0x20,
    },
    [RELAY_4] =
    {
        .pin = 9,
        .description = "Relay4",
        .i2cAddress = 0x20,
    },
    [RELAY_5] =
    {
        .pin = 5,
        .description = "Relay5",
        .i2cAddress = 0x20,
    },
    [RELAY_6] =
    {
        .pin = 10,
        .description = "Relay6",
        .i2cAddress = 0x20,
    },
    [RELAY_7] =
    {
        .pin = 4,
        .description = "Relay7",
        .i2cAddress = 0x20,
    },
    [RELAY_8] =
    {
        .pin = 11,
        .description = "Relay8",
        .i2cAddress = 0x20,
    }
};

const uint8_t m_lights_size = sizeof( m_lights ) / sizeof( m_lights[0] );
const uint8_t m_relays_size = sizeof( m_relays ) / sizeof( m_relays[0] );

#endif /* DATABASE_H */