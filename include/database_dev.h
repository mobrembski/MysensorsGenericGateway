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
        .pin = 15,
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
        .pin = 13,
        .description = "Switch3",
        .relayId = RELAY_3,
        .inactive = false,
        .i2cAddress = 0x20,
    },
    [SWITCH_4] =
    {
        .pin = 12,
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
        .i2cAddress = 0x20,
    },
    [SWITCH_6] =
    {
        .pin = 10,
        .description = "Switch6",
        .relayId = RELAY_6,
        .inactive = false,
        .i2cAddress = 0x20,
    },
    [SWITCH_7] =
    {
        .pin = 9,
        .description = "Switch7",
        .relayId = RELAY_7,
        .inactive = false,
        .i2cAddress = 0x20,
    },
    [SWITCH_OGROD] =
    {
        .pin = 8,
        .description = "Switch8",
        .relayId = RELAY_8,
        .inactive = false,
        .i2cAddress = 0x20,
    }
};

static tRelay m_relays[] =
{
    [RELAY_1] =
    {
        .pin = 0,
        .description = "Relay1",
        .i2cAddress = 0x20,
    },
    [RELAY_2] =
    {
        .pin = 1,
        .description = "Relay2",
        .i2cAddress = 0x20,
    },
    [RELAY_3] =
    {
        .pin = 2,
        .description = "Relay3",
        .i2cAddress = 0x20,
    },
    [RELAY_4] =
    {
        .pin = 3,
        .description = "Relay4",
        .i2cAddress = 0x20,
    },
    [RELAY_5] =
    {
        .pin = 4,
        .description = "Relay5",
        .i2cAddress = 0x20,
    },
    [RELAY_6] =
    {
        .pin = 5,
        .description = "Relay6",
        .i2cAddress = 0x20,
    },
    [RELAY_7] =
    {
        .pin = 6,
        .description = "Relay7",
        .i2cAddress = 0x20,
    },
    [RELAY_8] =
    {
        .pin = 7,
        .description = "Relay8",
        .i2cAddress = 0x20,
    }
};

const uint8_t m_lights_size = sizeof( m_lights ) / sizeof( m_lights[0] );
const uint8_t m_relays_size = sizeof( m_relays ) / sizeof( m_relays[0] );

#endif /* DATABASE_H */