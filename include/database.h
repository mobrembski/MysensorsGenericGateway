#ifndef DATABASE_H
#define DATABASE_H

#include "database_types.h"
#include "callbacks.h"

typedef enum {
  SWITCH_WEJSCIE = 0,  // 1 Pojedynczy /30 OK 25?
  SWITCH_PIWNICA,      // 2 Pojedynczy /29 OK 29
  SWITCH_KOR_PARTER,   // 3 /28 OK 1
  SWITCH_PRZEDPOKOJ,   // - Podwojny
  SWITCH_KOR_PARTER_2, // 4 Pojedynczy /27 OK 1
  SWITCH_TOALETA,      // 5 Pojedynczy /26 NOK? jest inactive sprawdzic dlaczego
  SWITCH_KUCHNIA_1,    // 6            /25 OK 13
  SWITCH_KUCHNIA_2,    // 7 Podwojny   /24 NOK? Dlaczego na pinie 21 jest tylko 1.1V?
  SWITCH_KUCHNIA_LED,  // 8 Pojedynczy /23 NOK? Dlaczego na pinie 20 jest 1.1V?
  SWITCH_SALON1_1,     // 9            /6 OK
  SWITCH_SALON1_2,     // 10 Podwojny  /7 OK
  SWITCH_SALON2_1,     // 11           /8 OK
  SWITCH_SALON2_2,     // 12 Podwojny  /9 OK
  SWITCH_SALON_KINKIETY,// 13 Pojedynczy /10 - NOK Do Zmiany! zajęte przez SPI EN
  SWITCH_SCHODY,       // 14 Pojedynczy - automatyka dla kinkietow /11 OK 7
  SWITCH_SCHODY_KINKIETY, // 15          /12 OK 6
  SWITCH_SCHODY_GORA,   // 16            /13 OK 7
  SWITCH_SCHODY_GORA_KINKIETY, // 17     /A14 OK 6
  SWITCH_BALKON,       // 18            /A13 OK 27
  SWITCH_KOR_PIETRO,    // 19 Potrojny?  /A12 OK 4
  SWITCH_KOR_PIETO_NOCNE, // 20          /A11 OK 5 - DO wywalenia?
  SWITCH_SYPIALNIA_1,   // 21            /A10  OK 18
  SWITCH_SYPIALNIA_2,   // 22 Podwojny   /A9 OK 19
  SWITCH_TARAS,        // 23            /A8 OK 28 
  SWITCH_OGROD,        // 24 Podwojny   /A7 OK 32
  SWITCH_GABINET_1,    // 25            /A6 OK 16
  SWITCH_GABINET_2,    // 26 Podwojny   /A5 OK 17
  SWITCH_LAZIENKA,     // 27 Pojedynczy - automatyka dla nocnego /A4
  SWITCH_DZIECKO_1,    // 28            /A3
  SWITCH_DZIECKO_2,    // 29 Podwojny   /A2 OK 21
  SWITCH_PRALNIA,      // 31            /A1 (A15?) OK 30 
  SWITCH_GARAZ,        // 32            /A0 OK 31
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
  { // SWITCH_WEJSCIE
    .pin = 30,
    .description = "WlacznikGanek",
    .relayId = RELAY_WEJSCIE,
  },
  { // SWITCH_PIWNICA
    .pin = 29,
    .description = "WlacznikPiwnica",
    .relayId = RELAY_PIWNICA,
  },
  { // SWITCH_KOR_PARTER
    .pin = 28,
    .description = "WlacznikKorParter",
    .relayId = RELAY_KOR_PARTER_1,
  },
  { // SWITCH_PRZEDPOKOJ
    .pin = 27,
    .description = "WlacznikPrzedpokoj",
    .relayId = RELAY_KOR_PARTER_1,
  },
  { // SWITCH_KOR_PARTER_2
    .pin = 27,
    .description = "WlacznikKorParter2",
    .relayId = RELAY_KOR_PARTER_2,
    .inactive = true,
  },
  { // SWITCH_TOALETA
    .pin = 26,
    .description = "WlacznikToaleta",
    .relayId = RELAY_TOALETA,
    .inactive = true,
  },
  { // SWITCH_KUCHNIA_1
    .pin = 25,
    .description = "WlacznikKuchnia1",
    .relayId = RELAY_KUCHNIA_1,
  },
  { // SWITCH_KUCHNIA_2
    .pin = 24,
    .description = "WlacznikKuchnia2",
    .relayId = RELAY_KUCHNIA_2,
  },
  { // SWITCH_KUCHNIA_LED
    .pin = 23,
    .description = "WlacznikKuchniaLED",
    .relayId = RELAY_KUCHNIA_LED,
  },
  { // SWITCH_SALON1_1
    .pin = 6,
    .description = "WlacznikSalon11",
    .relayId = RELAY_SALON1_1,
  },
  { // SWITCH_SALON1_2
    .pin = 7,
    .description = "WlacznikSalon12",
    .relayId = RELAY_SALON1_2,
  },
  { // SWITCH_SALON2_1
    .pin = 8,
    .description = "WlacznikSalon21",
    .relayId = RELAY_SALON2_1,
  },
  { // SWITCH_SALON2_2
    .pin = 9,
    .description = "WlacznikSalon22",
    .relayId = RELAY_SALON2_2,
  },
  { // SWITCH_SALON_KINKIETY
    .pin = 10,
    .description = "WlacznikSalonKinkiety",
    .relayId = RELAY_SALON_KINKIETY,
    .inactive = true,
  },
  { // SWITCH_SCHODY
    .pin = 11,
    .description = "WlacznikSchody",
    .relayId = RELAY_SCHODY,
  },
  { // SWITCH_SCHODY_KINKIETY
    .pin = 12,
    .description = "WlacznikSchodyKinkiety",
    .relayId = RELAY_SCHODY_KINKIETY,
  },
  { // SWITCH_SCHODY_GORA
    .pin = 13,
    .description = "WlacznikSchodyGora",
    .relayId = RELAY_SCHODY,
  },
  { // SWITCH_SCHODY_GORA_KINKIETY
    .pin = A14,
    .description = "WlacznikSchodyGoraKinkiety",
    .relayId = RELAY_SCHODY_KINKIETY,
  },
  { // SWITCH_BALKON
    .pin = A13,
    .description = "WlacznikBalkon",
    .relayId = RELAY_BALKON,
  },
  { // SWITCH_KOR_PIETRO
    .pin = A12,
    .description = "WlacznikKorPietro",
    .relayId = RELAY_KOR_PIETRO_1,
  },
  { // SWITCH_KOR_PIETO_NOCNE
    .pin = A11,
    .description = "WlacznikKorPietroNocne",
    .relayId = RELAY_KOR_PIETRO_2,
  },
  { // SWITCH_SYPIALNIA_1
    .pin = A10,
    .description = "WlacznikSypialnia1",
    .relayId = RELAY_SYPIALNIA_1,
  },
  { // SWITCH_SYPIALNIA_2
    .pin = A9,
    .description = "WlacznikSypialnia2",
    .relayId = RELAY_SYPIALNIA_2,
  },
  { // SWITCH_TARAS
    .pin = A8,
    .description = "WlacznikTaras",
    .relayId = RELAY_TARAS,
  },
  { // SWITCH_OGROD
    .pin = A7,
    .description = "WlacznikOgrod",
    .relayId = RELAY_OGROD,
  },
  { // SWITCH_GABINET_1
    .pin = A6,
    .description = "WlacznikGabinet1",
    .relayId = RELAY_GABINET_1,
  },
  { // SWITCH_GABINET_2
    .pin = A5,
    .description = "WlacznikGabinet2",
    .relayId = RELAY_GABINET_2,
  },
  { // SWITCH_LAZIENKA
    .pin = A4,
    .description = "WlacznikLazienka",
    .relayId = RELAY_LAZIENKA_1,
  },
  { // SWITCH_DZIECKO_1
    .pin = A3,
    .description = "WlacznikDziecko1",
    .relayId = RELAY_DZIECKO_1,
  },
  { // SWITCH_DZIECKO_2
    .pin = A2,
    .description = "WlacznikDziecko1",
    .relayId = RELAY_DZIECKO_2,
  },
  { // SWITCH_PRALNIA
    .pin = A15,
    .description = "WlacznikPralnia",
    .relayId = RELAY_KOTLOWNIA,
  },
  { // SWITCH_GARAZ
    .pin = A0,
    .description = "WlacznikGaraz",
    .relayId = RELAY_GARAZ,
    .inactive = false,
    .longPressCallback = &garageLongPress,
  }
};

static tRelay m_relays[] =
{
  { // RELAY_KOR_PARTER_1
    .pin = 42,
    .description = "SwiatloKorParter1",
  },
  { // RELAY_KOR_PARTER_2
    .pin = 41,
    .description = "SwiatloKorParter2",
  },
  { // RELAY_PRZEDPOKOJ
    .pin = 40,
    .description = "SwiatloPrzedpokoj",
  },
  { // RELAY_KOR_PIETRO_1
    .pin = 39,
    .description = "SwiatloKorPietro1",
  },
  { // RELAY_KOR_PIETRO_2
    .pin = 38,
    .description = "SwiatloKorPietro2",
  },
  { // RELAY_SCHODY_KINKIETY
    .pin = 37,
    .description = "SwiatloSchodyKinkiety",
  },
  { // RELAY_SCHODY
    .pin = 36,
    .description = "SwiatloSchody",
  },
  { // RELAY_SALON1_1
    .pin = 35,
    .description = "SwiatloSalon11",
  },
  { // RELAY_SALON1_2
    .pin = 34,
    .description = "SwiatloSalon12",
  },
  { // RELAY_SALON2_1
    .pin = 33,
    .description = "SwiatloSalon21",
  },
  { // RELAY_SALON2_2
    .pin = 32,
    .description = "SwiatloSalon22",
  },
  { // RELAY_SALON_KINKIETY
    .pin = 31,
    .description = "SwiatloSalonKinkiety",
  },
  { // RELAY_KUCHNIA_1
    .pin = 22,
    .description = "SwiatloKuchnia1",
  },
  { // RELAY_KUCHNIA_2
    .pin = 21,
    .description = "SwiatloKuchnia2",
  },
  { // RELAY_KUCHNIA_LED
    .pin = 20,
    .description = "SwiatloKuchniaLED",
  },
  { // RELAY_GABINET_1
    .pin = 19,
    .description = "SwiatloGabinet1",
  },
  { // RELAY_GABINET_2
    .pin = 18,
    .description = "SwiatloGabinet2",
  },
  { // RELAY_SYPIALNIA_1
    .pin = 17,
    .description = "SwiatloSypialnia1",
  },
  { // RELAY_SYPIALNIA_2
    .pin = 16,
    .description = "SwiatloSypialnia2",
  },
  { // RELAY_DZIECKO_1
    .pin = 15,
    .description = "SwiatloDziecko1",
  },
  { // RELAY_DZIECKO_2
    .pin = 14,
    .description = "SwiatloDziecko2",
  },
  { // RELAY_TOALETA
    .pin = 2,
    .description = "SwiatloToaleta",
  },
  { // RELAY_LAZIENKA_1
    .pin = 3,
    .description = "SwiatloLazienka1",
  },
  { // RELAY_LAZIENKA_2
    .pin = 4,
    .description = "SwiatloLazienka2",
  },
  { // RELAY_WEJSCIE
    .pin = 43,
    .description = "SwiatloWejscie",
  },
  { // RELAY_ULICA
    .pin = 44,
    .description = "SwiatloUlica",
  },
  { // RELAY_BALKON
    .pin = 45,
    .description = "SwiatloBalkon",
  },
  { // RELAY_TARAS
    .pin = 46,
    .description = "SwiatloTaras",
  },
  { // RELAY_PIWNICA
    .pin = 47,
    .description = "SwiatloPiwnica",
  },
  { // RELAY_KOTLOWNIA
    .pin = 48,
    .description = "SwiatloPralnia",
  },
  { // RELAY_GARAZ
    .pin = 49,
    .description = "SwiatloGaraż",
  },
  { // RELAY_LAZIENKA_NOCNE
    .pin = 50,
    .description = "SwiatloOgrod",
  },
  { // RELAY_LAZIENKA_NOCNE
    .pin = 51,
    .description = "SwiatloLazienkaNocne",
  }
};

const uint8_t m_lights_size = sizeof( m_lights ) / sizeof( m_lights[0] );
const uint8_t m_relays_size = sizeof( m_relays ) / sizeof( m_relays[0] );

#endif /* DATABASE_H */