#ifndef DATABASE_H
#define DATABASE_H

#include "database_types.h"
#include "callbacks.h"

#define MCP_COUNT_ON_I2C 4      /* Nuber of MCPs connected to board */
#define STAIRWAY_DIMM_PIN 4     /* Dimmable pin used for stairway brightness control */
#define NIGHTLIGHT_DIMM_PIN 13  /* Dimmable pin used for night light brightness control */

typedef enum {
  SWITCH_WEJSCIE = 0,
  SWITCH_PIWNICA,
  SWITCH_PRZEDPOKOJ,
  SWITCH_KOR_PARTER,
  SWITCH_TOALETA,
  SWITCH_KUCHNIA_1,
  SWITCH_KUCHNIA_2,
  SWITCH_KUCHNIA_LED,
  SWITCH_SALON1_1,
  SWITCH_SALON1_2,
  SWITCH_SALON2_1,
  SWITCH_SALON2_2,
  SWITCH_SALON_KINKIETY,
  SWITCH_SCHODY,
  SWITCH_SCHODY_KINKIETY,
  SWITCH_RYGIEL_GORA,
  SWITCH_RYGIEL_DOL,
  SWITCH_BALKON,
  SWITCH_KOR_PIETRO,
  SWITCH_KOR_PIETRO_NOCNE,
  SWITCH_SYPIALNIA_1,
  SWITCH_SYPIALNIA_2,
  SWITCH_TARAS,
  SWITCH_OGROD,
  SWITCH_GABINET_1,
  SWITCH_GABINET_2,
  SWITCH_LAZIENKA,
  SWITCH_LAZIENKA_2,
  SWITCH_DZIECKO_1,
  SWITCH_DZIECKO_2,
  SWITCH_GARAZ,
  SWITCH_PRALNIA,
  SWITCH_ULICA,        // DUMMY - control only via HA
  SWITCH_MAX_ID
} switchIds;

typedef enum {
  RELAY_KOR_PARTER_1 = 0,
  RELAY_KOR_PARTER_2,
  RELAY_PRZEDPOKOJ,
  RELAY_KOR_PIETRO_1,
  RELAY_KOR_PIETRO_2,
  RELAY_SCHODY_KINKIETY,
  RELAY_SCHODY,
  RELAY_SALON1_1,
  RELAY_SALON1_2,
  RELAY_SALON2_1,
  RELAY_SALON2_2,
  RELAY_SALON_KINKIETY,
  RELAY_KUCHNIA_1,
  RELAY_KUCHNIA_2,
  RELAY_KUCHNIA_LED,
  RELAY_GABINET_1,
  RELAY_GABINET_2,
  RELAY_SYPIALNIA_1,
  RELAY_SYPIALNIA_2,
  RELAY_DZIECKO_1,
  RELAY_DZIECKO_2,
  RELAY_TOALETA,
  RELAY_LAZIENKA_1,
  RELAY_LAZIENKA_2,
  RELAY_WEJSCIE,
  RELAY_ULICA,
  RELAY_BALKON,
  RELAY_TARAS,
  RELAY_PIWNICA,
  RELAY_KOTLOWNIA,
  RELAY_GARAZ,
  RELAY_OGROD,
  RELAY_LAZIENKA_NOCNE,
  RELAY_ZASIL_RYGIEL,
  RELAY_MAX_ID
} relayIds;

static tLightSwitch m_lights[] =
{
  [SWITCH_WEJSCIE] =
  {
    .pin = 1,
    .description = "WlacznikGanek",
    .relayId = RELAY_WEJSCIE,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
    .inactive = false,
    .i2cAddress = 0x20,
  },
  [SWITCH_PIWNICA] =
  {
    .pin = 14,
    .description = "WlacznikPiwnica",
    .relayId = RELAY_PIWNICA,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
    .inactive = false,
    .i2cAddress = 0x20,
  },
  [SWITCH_PRZEDPOKOJ] =
  {
    .pin = 0,
    .description = "WlacznikPrzedpokoj",
    .relayId = RELAY_PRZEDPOKOJ,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
    .inactive = false,
    .i2cAddress = 0x20,
  },
  [SWITCH_KOR_PARTER] =
  {
    .pin = 15,
    .description = "WlacznikKorParter",
    .relayId = RELAY_KOR_PARTER_1,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
    .inactive = false,
    .i2cAddress = 0x20,
  },
  [SWITCH_TOALETA] =
  {
    .pin = 42,
    .description = "WlacznikToaleta",
    .relayId = RELAY_TOALETA,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
    .inactive = false,
  },
  [SWITCH_KUCHNIA_1] =
  {
    .pin = 41,
    .description = "WlacznikKuchnia1",
    .relayId = RELAY_KUCHNIA_1,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
    .inactive = false,
  },
  [SWITCH_KUCHNIA_2] =
  {
    .pin = 40,
    .description = "WlacznikKuchnia2",
    .relayId = RELAY_KUCHNIA_2,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
    .inactive = false,
  },
  [SWITCH_KUCHNIA_LED] =
  {
    .pin = 39,
    .description = "WlacznikKuchniaLED",
    .relayId = RELAY_KUCHNIA_LED,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
    .inactive = false,
  },
  [SWITCH_SALON1_1] =
  {
    .pin = 1,
    .description = "WlacznikSalon11",
    .relayId = RELAY_SALON1_1,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
    .inactive = false,
    .i2cAddress = 0x21,
  },
  [SWITCH_SALON1_2] =
  {
    .pin = 14,
    .description = "WlacznikSalon12",
    .relayId = RELAY_SALON1_2,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
    .inactive = false,
    .i2cAddress = 0x21,
  },
  [SWITCH_SALON2_1] =
  {
    .pin = 0,
    .description = "WlacznikSalon21",
    .relayId = RELAY_SALON2_2,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
    .inactive = false,
    .i2cAddress = 0x21,
  },
  [SWITCH_SALON2_2] =
  {
    .pin = 15,
    .description = "WlacznikSalon22",
    .relayId = RELAY_SALON2_1,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
    .inactive = false,
    .i2cAddress = 0x21,
  },
  [SWITCH_SALON_KINKIETY] =
  {
    .pin = 38,
    .description = "WlacznikSalonKinkiety",
    .relayId = RELAY_SALON_KINKIETY,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
  },
  [SWITCH_SCHODY] =
  {
    .pin = 37,
    .description = "WlacznikSchody",
    .relayId = RELAY_SCHODY,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
  },
  [SWITCH_SCHODY_KINKIETY] =
  {
    .pin = 36,
    .description = "WlacznikSchodyKinkiety",
    .relayId = RELAY_SCHODY_KINKIETY,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
  },
  [SWITCH_RYGIEL_GORA] =
  {
    .pin = 35,
    .description = "RygielGora",
    .relayId = RELAY_MAX_ID,
    .datatype = V_ARMED,
    .sensortype = S_DOOR,
  },
  [SWITCH_RYGIEL_DOL] =
  {
    .pin = 33,
    .description = "RygielDol",
    .relayId = RELAY_MAX_ID,
    .datatype = V_ARMED,
    .sensortype = S_DOOR,
  },
  [SWITCH_BALKON] =
  {
    .pin = A13,
    .description = "WlacznikBalkon",
    .relayId = RELAY_BALKON,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
  },
  [SWITCH_KOR_PIETRO] =
  {
    .pin = A12,
    .description = "WlacznikKorPietro",
    .relayId = RELAY_KOR_PIETRO_1,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
  },
  [SWITCH_KOR_PIETRO_NOCNE] =
  {
    .pin = A11,
    .description = "WlacznikKorPietroNocne",
    .relayId = RELAY_KOR_PIETRO_2,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
  },
  [SWITCH_SYPIALNIA_1] =
  {
    .pin = A10,
    .description = "WlacznikSypialnia1",
    .relayId = RELAY_SYPIALNIA_1,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
  },
  [SWITCH_SYPIALNIA_2] =
  {
    .pin = A9,
    .description = "WlacznikSypialnia2",
    .relayId = RELAY_SYPIALNIA_2,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
  },
  [SWITCH_TARAS] =
  {
    .pin = A8,
    .description = "WlacznikTaras",
    .relayId = RELAY_TARAS,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
  },
  [SWITCH_OGROD] =
  {
    .pin = A7,
    .description = "WlacznikOgrod",
    .relayId = RELAY_OGROD,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
  },
  [SWITCH_GABINET_1] =
  {
    .pin = A6,
    .description = "WlacznikGabinet1",
    .relayId = RELAY_GABINET_1,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
  },
  [SWITCH_GABINET_2] =
  {
    .pin = A5,
    .description = "WlacznikGabinet2",
    .relayId = RELAY_GABINET_2,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
  },
  [SWITCH_LAZIENKA] =
  {
    .pin = A4,
    .description = "WlacznikLazienka",
    .relayId = RELAY_LAZIENKA_1,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
  },
  [SWITCH_LAZIENKA_2] =
  {
    .pin = A3,
    .description = "WlacznikLazienka2",
    .relayId = RELAY_LAZIENKA_2,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
  },
  [SWITCH_DZIECKO_1] =
  {
    .pin = A2,
    .description = "WlacznikDziecko1",
    .relayId = RELAY_DZIECKO_1,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
  },
  [SWITCH_DZIECKO_2] =
  {
    .pin = A1,
    .description = "WlacznikDziecko2",
    .relayId = RELAY_DZIECKO_2,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
  },
  [SWITCH_GARAZ] =
  {
    .pin = A0,
    .description = "WlacznikGaraz",
    .relayId = RELAY_GARAZ,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
    .inactive = false,
    .i2cAddress = 0x00,
    .longPressCallback = &garageLongPress,
  },
  [SWITCH_PRALNIA] =
  {
    .pin = A15,
    .description = "WlacznikPralnia",
    .relayId = RELAY_KOTLOWNIA,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
  },
  [SWITCH_ULICA] =
  {
    .pin = 32,
    .description = "WlacznikUlica",
    .relayId = RELAY_ULICA,
    .datatype = V_LIGHT,
    .sensortype = S_BINARY,
  },
};

static tRelay m_relays[] =
{
  [RELAY_KOR_PARTER_1] =
  {
    .pin = 7,
    .description = "SwiatloKorParter1",
    .i2cAddress = 0x20,
  },
  [RELAY_KOR_PARTER_2] =
  {
    .pin = 8,
    .description = "SwiatloKorParter2",
    .i2cAddress = 0x20
  },
  [RELAY_PRZEDPOKOJ] =
  {
    .pin = 6,
    .description = "SwiatloPrzedpokoj",
    .i2cAddress = 0x20,
  },
  [RELAY_KOR_PIETRO_1] =
  {
    .pin = 9,
    .description = "SwiatloKorPietro1",
    .i2cAddress = 0x20,
  },
  [RELAY_KOR_PIETRO_2] =
  {
    .pin = 5,
    .description = "SwiatloKorPietro2",
    .i2cAddress = 0x20,
  },
  [RELAY_SCHODY_KINKIETY] =
  {
    .pin = 10,
    .description = "SwiatloSchodyKinkiety",
    .i2cAddress = 0x20,
  },
  [RELAY_SCHODY] =
  {
    .pin = 4,
    .description = "SwiatloSchody",
    .i2cAddress = 0x20,
  },
  [RELAY_SALON1_1] =
  {
    .pin = 11,
    .description = "SwiatloSalon11",
    .i2cAddress = 0x20,
  },
  [RELAY_SALON1_2] =
  {
    .pin = 3,
    .description = "SwiatloSalon12",
    .i2cAddress = 0x20,
  },
  [RELAY_SALON2_1] =
  {
    .pin = 12,
    .description = "SwiatloSalon21",
    .i2cAddress = 0x20,
  },
  [RELAY_SALON2_2] =
  {
    .pin = 2,
    .description = "SwiatloSalon22",
    .i2cAddress = 0x20,
  },
  [RELAY_SALON_KINKIETY] =
  {
    .pin = 13,
    .description = "SwiatloSalonKinkiety",
    .i2cAddress = 0x20,
  },
  [RELAY_KUCHNIA_1] =
  {
    .pin = 7,
    .description = "SwiatloKuchnia1",
    .i2cAddress = 0x21,
  },
  [RELAY_KUCHNIA_2] =
  {
    .pin = 8,
    .description = "SwiatloKuchnia2",
    .i2cAddress = 0x21,
  },
  [RELAY_KUCHNIA_LED] =
  {
    .pin = 6,
    .description = "SwiatloKuchniaLED",
    .i2cAddress = 0x21,
  },
  [RELAY_GABINET_1] =
  {
    .pin = 9,
    .description = "SwiatloGabinet1",
    .i2cAddress = 0x21,
  },
  [RELAY_GABINET_2] =
  {
    .pin = 5,
    .description = "SwiatloGabinet2",
    .i2cAddress = 0x21,
  },
  [RELAY_SYPIALNIA_1] =
  {
    .pin = 10,
    .description = "SwiatloSypialnia1",
    .i2cAddress = 0x21,
  },
  [RELAY_SYPIALNIA_2] =
  {
    .pin = 4,
    .description = "SwiatloSypialnia2",
    .i2cAddress = 0x21,
  },
  [RELAY_DZIECKO_1] =
  {
    .pin = 11,
    .description = "SwiatloDziecko1",
    .i2cAddress = 0x21,
  },
  [RELAY_DZIECKO_2] =
  {
    .pin = 3,
    .description = "SwiatloDziecko2",
    .i2cAddress = 0x21,
  },
  [RELAY_TOALETA] =
  {
    .pin = 12,
    .description = "SwiatloToaleta",
    .i2cAddress = 0x21,
  },
  [RELAY_LAZIENKA_1] =
  {
    .pin = 2,
    .description = "SwiatloLazienka1",
    .i2cAddress = 0x21,
  },
  [RELAY_LAZIENKA_2] =
  {
    .pin = 13,
    .description = "SwiatloLazienka2",
    .i2cAddress = 0x21,
  },
  [RELAY_WEJSCIE] =
  {
    .pin = 43,
    .description = "SwiatloWejscie",
  },
  [RELAY_ULICA] =
  {
    .pin = 44,
    .description = "SwiatloUlica",
  },
  [RELAY_BALKON] =
  {
    .pin = 46,
    .description = "SwiatloBalkon",
  },
  [RELAY_TARAS] =
  {
    .pin = 45,
    .description = "SwiatloTaras",
  },
  [RELAY_PIWNICA] =
  {
    .pin = 47,
    .description = "SwiatloPiwnica",
  },
  [RELAY_KOTLOWNIA] =
  {
    .pin = 48,
    .description = "SwiatloPralnia",
  },
  [RELAY_GARAZ] =
  {
    .pin = 49,
    .description = "SwiatloGaraż",
  },
  [RELAY_OGROD] =
  {
    .pin = 50,
    .description = "SwiatloOgrod",
  },
  [RELAY_LAZIENKA_NOCNE] =
  {
    .pin = 51,
    .description = "SwiatloLazienkaNocne",
  },
  [RELAY_ZASIL_RYGIEL] =
  {
    .pin = 34,
    .description = "ZasilanieRygla",
  }
};

const uint8_t m_lights_size = sizeof( m_lights ) / sizeof( m_lights[0] );
const uint8_t m_relays_size = sizeof( m_relays ) / sizeof( m_relays[0] );

static MyMessage m_nightLight_dimmer;
static MyMessage m_stairway_dimmer;
static MyMessage m_nightLight_status;
static MyMessage m_stairway_status;

#endif /* DATABASE_H */