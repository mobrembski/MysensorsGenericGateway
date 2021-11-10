
This is a Arduino Sketch to control light switches from Home Assistant.

Main motivation to create this sketch was to create generic sketch which is easily
expandable if more switches/relays are needed.
It have following features:
- Based on MySensors library and PlatformIO
- Optional Support of MCP2307 I2C GPIO expanders ( with scanning I2C bus function )
- Optional Support of MQTT MySensors Ethernet client
- Support of customizable long press events
- Supports debouncing
- Optional support of BME280 environmental sensors

How to start

1. Download repo
2. Use git submodule to dowload required libs
   ```
   git submodule update --init --recursive
   ```
3. Open in VSCode with Platform.IO addons installed
4. Configure your installation in `config.h` and `database.h`. See below.
5. Build, Burn...

Database.h file

This file is source of all switches and relays.
It consist of two enums - `switchIds` and `relayIds`.
Every Switch has its own enumeration, which then is used in configuration arrays.
Configuration arrays are simmilar to enums - `static tLightSwitch m_lights[]` and `static tRelay m_relays[]`.

If you want to add another switch or relay, you must also add apropiate enum entries.

For field description see struct **tLightSwitch** and **tRelay** inside `database_types.h`
I think its pretty straight forward. If you want to another switch:
1. Add enum to relayIds representing relay which is driven by switch
2. Add enum to switchIds representing input switch pin, whis is driving relay
3. Place switch configuration inside m_lights in `database.h`:
   ```
    [SWITCH_SAMPLE] =
    {
      .pin = 14,
      .description = "SampleSwitchDescr",
      .relayId = RELAY_SAMPLE,
      .datatype = V_LIGHT,
      .sensortype = S_BINARY,
      .inactive = false,
      .i2cAddress = 0x20,
      .longPressCallback = &LongPressCallback,
    },
   ```

   Here we're indicating, that switch named **SWITCH_SAMPLE** is driving **RELAY_SAMPLE**, its description sent to HA is "SampleSwitchDescr".
   Switch we've just added is connected to pin 14 on I2C MCP expander at I2C address 0x20. Its sensor type is default for switch - S_BINARY -, like datatype - V_LIGHT. It has associated long press function - **LongPressCallback**

4. Place relay configuration inside m_relays in `database.h`:
   ```
    [RELAY_SAMPLE] =
    {
      .pin = 7,
      .description = "SampleRelayDescr",
      .i2cAddress = 0x20,
    },
   ```

   Here we're doing something simillar to switches, but is has way less options. Simillar to switch, we're denoting that relay **RELAY_SAMPLE** is connected
   to pin 7 on I2C MCP Expander at I2C address 0x20. It's description is "SampleRelayDescr"

5. Build, burn, run. You should see in logs that it founds new switch and relay and correctly sents to HA.

Notes:
- If you don't want to use MCP adapter (because you have builded without MCP Support in `config.h`, or just want to connect to Arduino GPIO pin), then just
  set **.i2cAddress** fields in `database.h` to 0x00 for corresponding switch/relay.
- If you wish to use Long press callback, then make sure you've added declaration of your used function inside `callbacks.h`, and definition inside `main.cpp` (or any other translation unit, but just be sure that function is not **static**).
- There is optional support of BME280, check `config.h`
- Also, MySensors configuration is also placed in `config.h`. If you don't want to use Ethernet gateway, you may just disable it.
