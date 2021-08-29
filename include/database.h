#ifndef DATABASE_H
#define DATABASE_H

#include "database_types.h"
#include "callbacks.h"

#define MCP_COUNT_ON_I2C 4

typedef enum {
  SWITCH_WEJSCIE = 0,  // 1 Pojedynczy /30
  SWITCH_PIWNICA,      // 2 Pojedynczy /29
  SWITCH_PRZEDPOKOJ,   // 3 Podwojny   /28
  SWITCH_KOR_PARTER,   // 4 Pojedynczy /27 OK 1
  SWITCH_TOALETA,      // 5 Pojedynczy /26 NOK? jest inactive sprawdzic dlaczego
  SWITCH_KUCHNIA_1,    // 6            /25 OK 13
  SWITCH_KUCHNIA_2,    // 7 Podwojny   /24 NOK? Dlaczego na pinie 21 jest tylko 1.1V?
  SWITCH_KUCHNIA_LED,  // 8 Pojedynczy /23 NOK? Dlaczego na pinie 20 jest 1.1V?
  SWITCH_SALON1_1,     // 9            /6 OK
  SWITCH_SALON1_2,     // 10 Podwojny  /7 OK
  SWITCH_SALON2_1,     // 11           /8 OK
  SWITCH_SALON2_2,     // 12 Podwojny  /9 OK
  SWITCH_SALON_KINKIETY,// 13 Pojedynczy /10 - NOK Do Zmiany! zajęte przez SPI EN
  SWITCH_SCHODY,       // 14 Pojedynczy /11
  SWITCH_SCHODY_KINKIETY, // 15          /12 OK 6
  SWITCH_SCHODY_GORA,   // 16            /13 OK 7
  SWITCH_SCHODY_GORA_KINKIETY, // 17     /A14 OK 6
  SWITCH_BALKON,       // 18            /A13 OK 27
  SWITCH_KOR_PIETRO,    // 19 Potrojny?  /A12 OK 4
  SWITCH_KOR_PIETRO_NOCNE, // 20          /A11 OK 5 - DO wywalenia?
  SWITCH_SYPIALNIA_1,   // 21            /A10  OK 18
  SWITCH_SYPIALNIA_2,   // 22 Podwojny   /A9 OK 19
  SWITCH_TARAS,        // 23            /A8 OK 28 
  SWITCH_OGROD,        // 24 Podwojny   /A7 OK 32
  SWITCH_GABINET_1,    // 25            /A6 OK 16
  SWITCH_GABINET_2,    // 26 Podwojny   /A5 OK 17
  SWITCH_LAZIENKA,     // 27 /A4
  SWITCH_LAZIENKA_2,   // 28 /A3
  SWITCH_DZIECKO_1,    // 29            /A2
  SWITCH_DZIECKO_2,    // 30 Podwojny   /A1 OK 21
  SWITCH_GARAZ,        // 31            /A0 OK 31
  SWITCH_PRALNIA,      // 32            /A15 OK 30 
  SWITCH_MAX_ID        // 28 sztuk
} switchIds;

// 8 pojedynczych
// 8 podwojnych

typedef enum {
  RELAY_KOR_PARTER_1 = 0, // 42
  RELAY_KOR_PARTER_2,     // 41
  RELAY_PRZEDPOKOJ,       // 40
  RELAY_KOR_PIETRO_1,     // 39
  RELAY_KOR_PIETRO_2,     // 38
  RELAY_SCHODY_KINKIETY,  // 37
  RELAY_SCHODY,           // 36
  RELAY_SALON1_1,         // 35
  RELAY_SALON1_2,         // 34
  RELAY_SALON2_1,         // 33
  RELAY_SALON2_2,         // 32
  RELAY_SALON_KINKIETY,   // 31
  RELAY_KUCHNIA_1,        // 22
  RELAY_KUCHNIA_2,        // 21
  RELAY_KUCHNIA_LED,      // 20
  RELAY_GABINET_1,        // 19
  RELAY_GABINET_2,        // 18
  RELAY_SYPIALNIA_1,      // 17
  RELAY_SYPIALNIA_2,      // 16
  RELAY_DZIECKO_1,        // 15
  RELAY_DZIECKO_2,        // 14
  RELAY_TOALETA,          // 2
  RELAY_LAZIENKA_1,       // 3
  RELAY_LAZIENKA_2,       // 4 // Nie uzywane
  RELAY_WEJSCIE,          // 43
  RELAY_ULICA,            // 44
  RELAY_BALKON,           // 45
  RELAY_TARAS,            // 46
  RELAY_PIWNICA,          // 47
  RELAY_KOTLOWNIA,        // 48
  RELAY_GARAZ,            // 49
  RELAY_OGROD,            // 50
  RELAY_LAZIENKA_NOCNE,   // 51
  RELAY_MAX_ID // 32 sztuk
} relayIds;

static tLightSwitch m_lights[] =
{
  [SWITCH_WEJSCIE] =
  {
    .pin = 1,
    .description = "WlacznikGanek",
    .relayId = RELAY_WEJSCIE,
    .inactive = false,
    .i2cAddress = 0x20,
  },
  [SWITCH_PIWNICA] =
  {
    .pin = 14,
    .description = "WlacznikPiwnica",
    .relayId = RELAY_PIWNICA,
    .inactive = false,
    .i2cAddress = 0x20,
  },
  [SWITCH_PRZEDPOKOJ] =
  {
    .pin = 0,
    .description = "WlacznikPrzedpokoj",
    .relayId = RELAY_PRZEDPOKOJ,
    .inactive = false,
    .i2cAddress = 0x20,
  },
  [SWITCH_KOR_PARTER] =
  {
    .pin = 15,
    .description = "WlacznikKorParter",
    .relayId = RELAY_KOR_PARTER_1,
    .inactive = false,
    .i2cAddress = 0x20,
  },
  [SWITCH_TOALETA] =
  {
    .pin = 42,
    .description = "WlacznikToaleta",
    .relayId = RELAY_TOALETA,
    .inactive = false,
  },
  [SWITCH_KUCHNIA_1] =
  {
    .pin = 41,
    .description = "WlacznikKuchnia1",
    .relayId = RELAY_KUCHNIA_1,
    .inactive = false,
  },
  [SWITCH_KUCHNIA_2] =
  {
    .pin = 40,
    .description = "WlacznikKuchnia2",
    .relayId = RELAY_KUCHNIA_2,
    .inactive = false,
  },
  [SWITCH_KUCHNIA_LED] =
  {
    .pin = 39,
    .description = "WlacznikKuchniaLED",
    .relayId = RELAY_KUCHNIA_LED,
    .inactive = false,
  },
  [SWITCH_SALON1_1] =
  {
    .pin = 1,
    .description = "WlacznikSalon11",
    .relayId = RELAY_SALON1_1,
    .inactive = false,
    .i2cAddress = 0x21,
  },
  [SWITCH_SALON1_2] =
  {
    .pin = 14,
    .description = "WlacznikSalon12",
    .relayId = RELAY_SALON1_2,
    .inactive = false,
    .i2cAddress = 0x21,
  },
  [SWITCH_SALON2_1] =
  {
    .pin = 0,
    .description = "WlacznikSalon21",
    .relayId = RELAY_SALON2_2,
    .inactive = false,
    .i2cAddress = 0x21,
  },
  [SWITCH_SALON2_2] =
  {
    .pin = 15,
    .description = "WlacznikSalon22",
    .relayId = RELAY_SALON2_1,  // SPrawdz!!
    .inactive = false,
    .i2cAddress = 0x21,
  },
  [SWITCH_SALON_KINKIETY] =
  {
    .pin = 38,
    .description = "WlacznikSalonKinkiety",
    .relayId = RELAY_SALON_KINKIETY,
  },
  [SWITCH_SCHODY] =
  {
    .pin = 37,
    .description = "WlacznikSchody",
    .relayId = RELAY_SCHODY,
  },
  [SWITCH_SCHODY_KINKIETY] =
  {
    .pin = 36,
    .description = "WlacznikSchodyKinkiety",
    .relayId = RELAY_SCHODY_KINKIETY,
  },
  [SWITCH_SCHODY_GORA] =
  {
    .pin = 35,
    .description = "WlacznikSchodyGora",
    .relayId = RELAY_SCHODY,
  },
  [SWITCH_SCHODY_GORA_KINKIETY] =
  {
    .pin = A14,
    .description = "WlacznikSchodyGoraKinkiety",
    .relayId = RELAY_SCHODY_KINKIETY,
  },
  [SWITCH_BALKON] =
  {
    .pin = A13,
    .description = "WlacznikBalkon",
    .relayId = RELAY_BALKON,
  },
  [SWITCH_KOR_PIETRO] =
  {
    .pin = A12,
    .description = "WlacznikKorPietro",
    .relayId = RELAY_KOR_PIETRO_1,
  },
  [SWITCH_KOR_PIETRO_NOCNE] =
  {
    .pin = A11,
    .description = "WlacznikKorPietroNocne",
    .relayId = RELAY_KOR_PIETRO_2,
  },
  [SWITCH_SYPIALNIA_1] =
  {
    .pin = A10,
    .description = "WlacznikSypialnia1",
    .relayId = RELAY_SYPIALNIA_1,
  },
  [SWITCH_SYPIALNIA_2] =
  {
    .pin = A9,
    .description = "WlacznikSypialnia2",
    .relayId = RELAY_SYPIALNIA_2,
  },
  [SWITCH_TARAS] =
  {
    .pin = A8,
    .description = "WlacznikTaras",
    .relayId = RELAY_TARAS,
  },
  [SWITCH_OGROD] =
  {
    .pin = A7,
    .description = "WlacznikOgrod",
    .relayId = RELAY_OGROD,
  },
  [SWITCH_GABINET_1] =
  {
    .pin = A6,
    .description = "WlacznikGabinet1",
    .relayId = RELAY_GABINET_1,
  },
  [SWITCH_GABINET_2] =
  {
    .pin = A5,
    .description = "WlacznikGabinet2",
    .relayId = RELAY_GABINET_2,
  },
  [SWITCH_LAZIENKA] =
  {
    .pin = A4,
    .description = "WlacznikLazienka",
    .relayId = RELAY_LAZIENKA_1,
  },
  [SWITCH_LAZIENKA_2] =
  {
    .pin = A3,
    .description = "WlacznikLazienka2",
    .relayId = RELAY_LAZIENKA_2,
  },
  [SWITCH_DZIECKO_1] =
  {
    .pin = A2,
    .description = "WlacznikDziecko1",
    .relayId = RELAY_DZIECKO_1,
  },
  [SWITCH_DZIECKO_2] =
  {
    .pin = A1,
    .description = "WlacznikDziecko2",
    .relayId = RELAY_DZIECKO_2,
  },
  [SWITCH_GARAZ] =
  {
    .pin = A0,
    .description = "WlacznikGaraz",
    .relayId = RELAY_GARAZ,
    .inactive = false,
    .i2cAddress = 0x00,
    .longPressCallback = &garageLongPress,
  },
  [SWITCH_PRALNIA] =
  {
    .pin = A15,
    .description = "WlacznikPralnia",
    .relayId = RELAY_KOTLOWNIA,
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
   // poprawic
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
  }
};

const uint8_t m_lights_size = sizeof( m_lights ) / sizeof( m_lights[0] );
const uint8_t m_relays_size = sizeof( m_relays ) / sizeof( m_relays[0] );

#endif /* DATABASE_H */