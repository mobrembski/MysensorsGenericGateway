#ifndef DATABASE_H
#define DATABASE_H

#include "database_types.h"
#include "callbacks.h"

/*
problemy: 
26 pin tj switch toaleta nie wykrywa stanu wysokiego
21 pin nie zmienia stanu, dlaczego?
20 pin stan wysoki to ok 0.9V dlaczego?
10 pin zajęty przez ethernet trzeba zmienic

Wyjścia:
1. Korytarz parter brązowy pin 42
2. Korytarz parter czarny pin 41
3. Przedpokój brązowy pin 40
4. Korytarz piętro brązowy pin 39 
5. Korytarz piętro czarny pin 38
6. (Schody kinkiety?) pin 37
7. (Schody ledy?) pin 36
8. Salon 1 brązowy pin 35
9. Salon 1 czarny pin 34
10. Salon 2 brązowy pin 33
11. Salon 2 czarny pin 32
12. (kinkiety brązowe?) pin 31 
13. Kuchnia brązowy pin 22
14. (Kuchnia czarny?) pin 21
15. (Kuchnia kinkiet?) pin 20
16. (Gabinet brązowy?) pin 19
17. (Gabinet czarny?) pin 18
18. Sypialnia brązowy pin 17
19. Sypialnia czarny pin 16
20. Dziecko brązowy pin 15
21. Dziecko czarny pin 14
22. Toaleta parter pin 2
23. (Łazienka brązowy?) pin 3 
24. (Łazienka czarny?) pin 4
25. (Ośw ganek?) pin 43
26. (Ośw przód domu?) pin 44 
27. (Ośw balkon?) pin 45
28. (ośw balkon?) pin 46
29. Piwnica pin 47
30. Pralnia pin 48
31. Garaż pin 49
32. Ogród pin 50
piny 51 52 i 53 podłączone do wyjść 33,34,35 nie wykorzystane
Wyjście 36 podłączone do niebieskiego, nie podłączone do płytki
Wejścia:
1. Ganek (przedpokój czarny) pin 30
2. Piwnica (przedpokój szary) pin 29
3. Przedpokój (przedpokój niebieski) pin 28
4. Korytarz parter (niebieski) pin 27
5. Toaleta parter (niebieski) pin 26
6. Kuchnia niebieski pin 25
7. Kucnia Czarny pin 24
8. Kuchnia szary pin 23
9. Salon 1 niebieski pin 6 
10. Salon 1 Czarny pin 7
11. Salon 2 niebieski pin 8 
12. Salon 2 czarny pin 9
13. Salon kinkiet niebieski pin 10
14. Schody dół niebieski pin 11
15. Schody dół czarny pin 12
16. Schody góra niebieski pin 13 
17. Schody góra 2 czarny pin A14
18. Schody góra szary pin A13
19. Schody góra 2 niebieski pin A12
20. Schody góra czarny pin A11
21. Sypialnia niebieski pin A10
22. Sypialnia czarny pin A09
23. Taras niebieski pin A08
24. Taras czarny pin A07
25. Gabinet niebieski pin A06
26. Gabinet czarny pin A05
27. Łazienka niebieski pin A04
28. Łazienka czarny pin A03
29. Dziecko niebieski pin A02
30. Dziecko czarny pin A01
31. Garaż pin A0
32. Pralnia pin A15
*/

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
  SWITCH_KOR_PIETO_NOCNE, // 20          /A11 OK 5 - DO wywalenia?
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
  { // SWITCH_PRZEDPOKOJ
    .pin = 28,
    .description = "WlacznikPrzedpokoj",
    .relayId = RELAY_PRZEDPOKOJ,
  },
  { // SWITCH_KOR_PARTER
    .pin = 27,
    .description = "WlacznikKorParter",
    .relayId = RELAY_KOR_PARTER_1,
  },
  { // SWITCH_TOALETA
    .pin = 26,
    .description = "WlacznikToaleta",
    .relayId = RELAY_TOALETA,
    .inactive = false,
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
  { // SWITCH_LAZIENKA_2
    .pin = A3,
    .description = "WlacznikLazienka2",
    .relayId = RELAY_LAZIENKA_2,
  },
  { // SWITCH_DZIECKO_1
    .pin = A2,
    .description = "WlacznikDziecko1",
    .relayId = RELAY_DZIECKO_1,
  },
  { // SWITCH_DZIECKO_2
    .pin = A1,
    .description = "WlacznikDziecko2",
    .relayId = RELAY_DZIECKO_2,
  },
  { // SWITCH_GARAZ
    .pin = A0,
    .description = "WlacznikGaraz",
    .relayId = RELAY_GARAZ,
    .inactive = false,
    .longPressCallback = &garageLongPress,
  },
  { // SWITCH_PRALNIA
    .pin = A15,
    .description = "WlacznikPralnia",
    .relayId = RELAY_KOTLOWNIA,
  },
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
    .pin = 46,
    .description = "SwiatloBalkon",
  },
  { // RELAY_TARAS
    .pin = 45,
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