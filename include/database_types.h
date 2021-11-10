/*
   database_types.h

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

#ifndef DATABASE_TYPES_H
#define DATABASE_TYPES_H

#include <core/MyMessage.h>

typedef void (*tLongPressCallback)(void);

typedef struct {
  const uint8_t pin;                    /* Pin used for switch. If i2cAddress is not 0, then it is MCP pin, otherwise is just normal Arduino pin */
  const char* description;              /* Switch text description sent to HA */
  const uint8_t relayId;                /* Id from relayIds, describes which relay is associated with switch. */
  const mysensors_data_t datatype;      /* Datatype from MySensors lib mysensors_data_t. Mostly V_LIGHT. */
  const mysensors_sensor_t sensortype;  /* Sensor type from MySensors lib mysensors_sensor_t. Mostly S_BINARY. */
  const bool inactive;                  /* Set to false if you want to disable switch. Disabled switch is not presented to HA. */
#ifdef MCP23017_SUPPORT
  const uint8_t i2cAddress;             /* I2C Address of MCP23017 to which pin is connected. It can be 0, meaning that it is associated to Arduino GPIO */
#endif
  tLongPressCallback longPressCallback; /* Optional function pointer executed when switch is long pressed. */
  /* Fields below are used by sketch and it shouldn't be modified. */
  bool currentState;
  
  bool lastState;
  bool startTimeout;
  unsigned long buttonPressStartTimeStamp;
  unsigned long buttonPressDuration;
  MyMessage* message;
} tLightSwitch;

typedef struct {
  const uint8_t pin;                    /* Pin used for relay. If i2cAddress is not 0, then it is MCP pin, otherwise is just normal Arduino pin */
  const char* description;              /* Relay text description sent to HA */
#ifdef MCP23017_SUPPORT
  const uint8_t i2cAddress;             /* I2C Address of MCP23017 to which pin is connected. It can be 0, meaning that it is associated to Arduino GPIO */
#endif
  /* Fields below are used by sketch and it shouldn't be modified. */
  bool currentState;
} tRelay;

#endif /* DATABASE_TYPES_H */