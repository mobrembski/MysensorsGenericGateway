// Main configuration is here:
#include "config.h"
#include "callbacks.h"

#ifdef DEVELOPER_BOARD
#include "database_dev.h"
#else
#include "database.h"
#endif

// LIBRARIES
#include <SPI.h>                                  // A communication backbone, the Serial Peripheral Interface.
#include <Ethernet.h>                             // Ethernet library
#include <MySensors.h>                            // The MySensors library. Hurray!
#include <Wire.h>                                 // Enables the Wire communication protocol.
#include <BouncerAdaptor.h>
#ifdef MCP23017_SUPPORT
#include <Adafruit_MCP23017.h>
#endif
#ifdef BME280_SUPPORT
#include <Adafruit_BME280.h>
#endif

#define MAX_UART_BUF_LEN          100             // UART Maxium buffer length
#define DEBOUNCE_INTERVAL         25              // Debounce interval in ms
#define PERIODIC_LIGHT_SEND       1               // Send light states periodically? 1 = Yes, 0 = No, only when switch change.
#define PERIODIC_LIGHT_INTERVAL   10000           // Interval between Light sends, button press is always send immediately
#ifdef MCP23017_SUPPORT
#define MAXIMUM_I2C_7BIT_ADDRESS  127             // Maximum I2C address when using 7 bit adressing
#define MCP_GPIO_COUNT            16              // Count of GPIO pins in MCP23017
#define MCP_MINIMUM_ADDRESS       0x20            // Lowest possible I2C address for MCP
#define MCP_MAXIMUM_ADDRESS       0x27            // Maximum possible I2C address for MCP
#endif
#ifdef BME280_SUPPORT
#define PERIODIC_BME_INTERVAL     10000           // Interval between BME reading send
#endif

#define noEvent                   0               // Return value for checkButton when no event occurs
#define shortPress                1               // Return value for checkButton when short press occurs
#define longPress                 2               // Return value for checkButton when long press occurs
#define shortTime                 800             // Button press time in ms for short press
#define longTime                  1200             // Button press time in ms for long press

static BouncerAdaptor* debouncers[SWITCH_MAX_ID];
static char uartBuffer[MAX_UART_BUF_LEN];
unsigned long m_lights_send_interval = PERIODIC_LIGHT_INTERVAL;
static bool m_i2c_hasDevices;

#ifdef MCP23017_SUPPORT
static Adafruit_MCP23017 mcpAdapter[MCP_COUNT_ON_I2C];
#endif

#ifdef BME280_SUPPORT
static bool bme280Initialized;
static unsigned long previousBmeMillis;
static unsigned long m_bme_send_interval = PERIODIC_BME_INTERVAL;
static Adafruit_BME280 bme280;
static MyMessage bme280Temp( SWITCH_MAX_ID + 0, V_TEMP);
static MyMessage bme280Hum( SWITCH_MAX_ID + 1, V_HUM);
static MyMessage bme280Press( SWITCH_MAX_ID + 2, V_PRESSURE);
#endif

void printUart( const char *format, ...) {
  va_list args;
  va_start( args, format );
  vsprintf( uartBuffer, format, args );
  Serial.print( uartBuffer );
  Serial.print( "\r\n" );
  va_end( args );
}

void configurePins() {
  for( size_t i = 0; i < m_lights_size; ++i ) {
    tLightSwitch* light = &m_lights[i];
    printUart( "Switch %u pin %u %s", i, light->pin, light->description );
    if( !light->inactive )
    {
      pinMode( light->pin, INPUT );
      light->message = new MyMessage( i, V_STATUS );
      light->currentState = 0;
      light->lastState = 0;
    }
    else
    {
      printUart( "Switch %u pin %u %s is inactive!", i, light->pin, light->description );
    }
  }
  for( size_t i = 0; i < m_relays_size; ++i ) {
    const tRelay* relay = &m_relays[i];
    printUart( "Relay %u pin %u %s", i, relay->pin, relay->description );
    pinMode( relay->pin, OUTPUT );
    digitalWrite( relay->pin, 0);
    if( relay->currentState )
    {
      //digitalWrite( relay->pin, relay->currentState );
    }
  }
}

void configureDebouncers() {
  for( size_t i = 0; i < m_lights_size; ++i ) {
    tLightSwitch* light = &m_lights[i];

    if( !light->inactive )
    {
      printUart( "Configuring debouncer for Switch %u pin %u %s", i, light->pin, light->description );
#ifdef MCP23017_SUPPORT
      if( light->i2cAddress > 0 )
      {
        uint8_t realI2cAddress = light->i2cAddress;
        if( ( realI2cAddress >= MCP_MINIMUM_ADDRESS ) &&
            ( realI2cAddress <= MCP_MAXIMUM_ADDRESS ) )
        {
          printUart( "    Switch is assigned to MCP adapter at address 0x%2X", light->i2cAddress );
          if( m_i2c_hasDevices ) // Ugly hack, remove this if
          {
            debouncers[i] = new BouncerAdaptor( mcpAdapter[realI2cAddress - MCP_MINIMUM_ADDRESS], light->pin );
            debouncers[i]->interval( DEBOUNCE_INTERVAL );
          }
          else
          {
            printUart( "    ERROR: Ommiting due to disabled I2C" );
          }
        }
        else
        {
          printUart( "    ERROR! Switch has incompatible I2C Address 0x%2X !", light->i2cAddress );
        }
      }
      else
#endif
      {
        printUart( "    is normal pin" );
        debouncers[i] = new BouncerAdaptor( light->pin );
        debouncers[i]->interval( DEBOUNCE_INTERVAL );
      }
    }
    else
    {
      printUart( "    Ommiting due to inactive flag!" );
    }
  }
}

#ifdef MCP23017_SUPPORT
void configureMcpAdapter( uint8_t mcpAddress ) {
  uint8_t index = mcpAddress - MCP_MINIMUM_ADDRESS;
  if( m_i2c_hasDevices )
  {
    mcpAdapter[index].begin(index, &Wire);
  }
  for( size_t i = 0; i < m_lights_size; ++i ) {
    tLightSwitch* light = &m_lights[i];
    if( ( !light->inactive ) &&
        ( light->i2cAddress == mcpAddress ) )
    {
      if( ( light->pin >= 0 ) &&
          ( light->pin <= MCP_GPIO_COUNT) )
      {
        printUart( "Switch %u pin %u %s is using MCP at addrs 0x%2X idx %u", i, light->pin, light->description, light->i2cAddress, index );
        if( m_i2c_hasDevices )
        {
          mcpAdapter[index].pinMode( light->pin, INPUT );
          printUart("    Configuring device 0x%2X pin 0x%2X", mcpAddress, light->pin);
          //mcpAdapter[index].pullUp( light->pin, LOW );
          printUart("    Configuring device 0x%2X pin 0x%2X pullup", mcpAddress, light->pin);
        }
        else
        {
          printUart( "    ERROR: Ommiting due to disabled I2C");
        }
      }
      else
      {
        printUart("    ERROR: Switch %u pin %u %s is using MCP but with wrong PIN ID! ", i, light->pin, light->description );
      }
      
    }
  }
  for( size_t i = 0; i < m_relays_size; ++i ) {
    const tRelay* relay = &m_relays[i];
    if( relay->i2cAddress == mcpAddress )
    {
      if( ( relay->pin >= 0 ) &&
          ( relay->pin <= MCP_GPIO_COUNT) )
      {
        printUart( "Relay %u pin %u %s is using MCP at addrs 0x%2X", i, relay->pin, relay->description, relay->i2cAddress );
        if( m_i2c_hasDevices )
        {
          mcpAdapter[index].pinMode( relay->pin, OUTPUT );
          printUart("   Configuring device 0x%2X pin 0x%2X", mcpAddress, relay->pin);
        }
        else
        {
          printUart( "    ERROR: Ommiting due to disabled I2C");
        }
      }
      else
      {
        printUart("    ERROR: Relay %u pin %u %s is using MCP but with wrong PIN ID! ", i, relay->pin, relay->description );
      }
    }
    printUart( "Relay %u pin %u %s", i, relay->pin, relay->description );
  }
}

#endif

#ifdef BME280_SUPPORT
void configureBme280() {
  bme280Initialized = bme280.begin();
  if ( !bme280Initialized ) {
    printUart("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    printUart("SensorID was: 0x2X", bme280.sensorID() );
    printUart("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    printUart("   ID of 0x56-0x58 represents a BMP 280,\n");
    printUart("        ID of 0x60 represents a BME 280.\n");
  }
}
#endif

// patrzac na przod gdzie gora to trapez:
// 1. SCL
// 2. GND
// 3. SDA
#ifdef I2C_SCANNER_SUPPORT
bool i2cHasDevices() {
  bool hasDevices = true;
  pinMode(20,INPUT);
  pinMode(21,INPUT);
  if ( digitalRead(20) != 1 ) {
    printUart( "ERROR: SDA pin is LOW!");
    hasDevices = false;
  }
  if ( digitalRead(21) != 1 ) {
    printUart( "ERROR: SCL pin is LOW!");
    hasDevices = false;
  }
  return hasDevices;
}

uint8_t i2cscanner( uint8_t (&devicesOutputTable)[MAXIMUM_I2C_7BIT_ADDRESS] ) {
  byte error, address;
  uint8_t nDevices = 0;

  if( m_i2c_hasDevices )
  {
    printUart( "Scanning I2C Bus..." );
    for( address = 1; address < MAXIMUM_I2C_7BIT_ADDRESS; address++ ) {
      // The i2c_scanner uses the return value of
      // the Write.endTransmisstion to see if
      // a device did acknowledge to the address.
      devicesOutputTable[ address ] = 0;
      Wire.beginTransmission( address );
      error = Wire.endTransmission();

      if( error == 0 )
      {
        printUart( "   I2C device found at address 0x%2X !", address );
        devicesOutputTable[ address ] = 1;

  #ifdef MCP23017_SUPPORT
        if( ( address >= MCP_MINIMUM_ADDRESS ) &&
            ( address <= MCP_MAXIMUM_ADDRESS ) ) {
          printUart( "      It seems that it is %u MCP23017 Adapter!", address - MCP_MINIMUM_ADDRESS );
        }
  #endif

  #ifdef BME280_SUPPORT
        if( address == 0x76 || address == 0x77 ) {
          printUart( "      It seems that it is BME280 sensor!" );
        }
  #endif

        nDevices++;
      }
      else if( error == 4 )
      {
        printUart( "   Unknown error %u at address 0x%2X !", error, address );
      }
    }
    printUart( nDevices == 0 ? "No I2C devices found" : "Scanning I2C done" );
  }
  else
  {
    printUart( "ERROR: I2C Bus scanning disabled due to no devices found on bus" );
  }
  
  return nDevices;
}
#endif

void setup() {
  Serial.begin(115200);
  printUart("Hello %s!", MY_HOSTNAME );
  m_i2c_hasDevices = i2cHasDevices();
  if( m_i2c_hasDevices )
  {
    Wire.begin();
  }
  else
  {
    printUart( "I2C Bus pins in LOW state, no devices? Please check connection");
  }
  configurePins();
#ifdef I2C_SCANNER_SUPPORT
  uint8_t i2cDevicesMap[MAXIMUM_I2C_7BIT_ADDRESS];
  memset( i2cDevicesMap, 0, MAXIMUM_I2C_7BIT_ADDRESS);
  i2cscanner(i2cDevicesMap);

#ifdef MCP23017_SUPPORT
  for( uint8_t addr = MCP_MINIMUM_ADDRESS; addr <= MCP_MAXIMUM_ADDRESS; ++addr )
  {
    if( i2cDevicesMap[addr] != 0 ) {
      configureMcpAdapter(addr);
    }
  }
#endif

#ifdef BME280_SUPPORT
  if( ( i2cDevicesMap[BME280_ADDRESS] != 0 ) ||
      ( i2cDevicesMap[BME280_ADDRESS_ALTERNATE] != 0 ) ) {
    configureBme280();
  }
#endif

#else /* I2C_SCANNER_SUPPORT */

  // No scan was done before, so we belive that adapters exists on bus
#ifdef MCP23017_SUPPORT
  configureMcpAdapters();
#endif
#ifdef BME280_SUPPORT
  configureBme280();
#endif

#endif /* I2C_SCANNER_SUPPORT */
  configureDebouncers();
  printUart("Done configuring all");
}


void presentation()  {
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo( MY_HOSTNAME, SKETCH_VERSION );

  // Tell the MySensors gateway what kind of sensors this node has, and what their ID's on the node are, as defined in the code above.
  for(size_t i = 0; i < m_lights_size; ++i ) {
    present( i, S_BINARY, m_lights[i].description );
  }

  // "Inclusion mode for HA"
  if(digitalRead(m_lights[0].pin) == HIGH)
  {
    printUart( "Sending all fake states of relays" );
    for( size_t i = 0; i < m_lights_size; ++i ) {
      MyMessage* message = m_lights[i].message;
      send(*message);
      message->set( true );
      send(*message);
      message->set( false );
    }
  }
  printUart( "Presentation done." );
}

byte checkButton(tLightSwitch* light, BouncerAdaptor* button)
{
  if( ( light->i2cAddress > 0 ) && 
      ( !m_i2c_hasDevices ) )
  {
    return noEvent;
  }
  if( ( light->i2cAddress > 0 ) && 
      ( m_i2c_hasDevices ) )
  {
    uint8_t realI2cAddress = light->i2cAddress;
    if( ( realI2cAddress < MCP_MINIMUM_ADDRESS ) ||
        ( realI2cAddress > MCP_MAXIMUM_ADDRESS ) )
    {
      printUart( "ERROR: i2cAddress is not in MCP range, omitting checking light %s", light->description);
      return noEvent;
    }
  }
  byte event = noEvent;
  // Update the Bounce instance, does digitalRead of button
  button->update();
  // Button press transition from LOW to HIGH)
  if (button->rose())
  {
    light->buttonPressStartTimeStamp = millis();
    light->startTimeout = true;
  }

  // Button release transition from HIGH to LOW) :
  if (button->fell())
  {
    light->buttonPressDuration = (millis() - light->buttonPressStartTimeStamp);
    printUart("Button %s press duration %u ms", light->description, light->buttonPressDuration);
    light->startTimeout = false;
  }

  if ( light->buttonPressDuration > 0 && light->buttonPressDuration <= shortTime)
  {
    event = shortPress;
    light->buttonPressDuration = 0;
  }

  if (light->startTimeout == true && (millis() - light->buttonPressStartTimeStamp) > longTime)
  {
    event = longPress;
    light->startTimeout = false;
    light->buttonPressDuration = 0;
    printUart("Button %s press timeout", light->description);
  }
  return event;
}

void switchRelayForLight(tRelay* relay, tLightSwitch* light)
{
    if( light->currentState != light->lastState )
    {
        printUart("SwitchingState %s to %d", relay->description, light->currentState);
        light->lastState = light->currentState;
        relay->currentState = light->currentState;
#ifdef MCP23017_SUPPORT
        if( relay->i2cAddress > 0 )
        {
            uint8_t realI2cAddress = relay->i2cAddress;
            if( ( realI2cAddress >= MCP_MINIMUM_ADDRESS ) &&
                ( realI2cAddress <= MCP_MAXIMUM_ADDRESS ) )
            {
                printUart( "    Relay is assigned to MCP adapter at address 0x%2X", relay->i2cAddress );
                if( m_i2c_hasDevices ) // Ugly hack, remove this if
                {
                    mcpAdapter[realI2cAddress - MCP_MINIMUM_ADDRESS].digitalWrite( relay->pin, relay->currentState );
                }
                else
                {
                    printUart( "    ERROR: Ommiting due to disabled I2C" );
                }
            }
            else
            {
                printUart( "    ERROR! Relay has incompatible I2C Address 0x%2X !", light->i2cAddress );
            }
        }
        else
#endif
        {
            digitalWrite(relay->pin, relay->currentState);
        }
    }
}

void garageLongPress()
{
  tLightSwitch* ogrodekLight = &m_lights[SWITCH_OGROD];
  tRelay* relay =  &m_relays[ogrodekLight->relayId];
  printUart("LongPress %s", ogrodekLight->description);
  ogrodekLight->currentState = !ogrodekLight->currentState;
  switchRelayForLight(relay, ogrodekLight);
}

void loop() {

  // You should not change these variables:
  static unsigned long previousLightMillis = 0;  // Used to remember the time that the BME280 sensor was asked for a measurement.
  unsigned long currentMillis = millis();         // The time since the sensor started, counted in milliseconds. This script tries to avoid using the Sleep function, so that it could at the same time be a MySensors repeater.
  for( size_t i = 0; i < m_lights_size; ++i ) {
    tLightSwitch* light = &m_lights[i];
    if( !light->inactive )
    {
      BouncerAdaptor* debouncer = debouncers[i];
      byte buttonEvent = checkButton(light, debouncer);
      switch(buttonEvent)
      {
        case shortPress:
          printUart( "Button %d %s pressed...", i, light->description );
          light->currentState = !light->currentState;
          break;
        case longPress:
          printUart( "Button %d %s long pressed...", i, light->description );
          if( light->longPressCallback != NULL )
          {
            light->longPressCallback();
          }
          else /* If no long press, then behave like normal click */
          {
            light->currentState = !light->currentState;
          }
          break;
      }
#ifdef STANDALONE_MODE
      if( light->relayId != RELAY_MAX_ID )
      {
        tRelay* relay = &m_relays[light->relayId];
        switchRelayForLight(relay, light);
      }
#endif
    }
  }

  if( ( PERIODIC_LIGHT_SEND ) &&
      ( currentMillis - previousLightMillis >= m_lights_send_interval ) ) {
      printUart("Periodic send of Light state...");
      for( size_t i = 0; i < m_lights_size; ++i ) {
          previousLightMillis = currentMillis;
          tLightSwitch* light = &m_lights[i];
          send( *light->message );
      }
      printUart("End of periodic send of Light state...");
  }

#ifdef BME280_SUPPORT
  if( ( bme280Initialized ) &&
      ( currentMillis - previousBmeMillis >= m_bme_send_interval )) {
        float temperature = bme280.readTemperature();
        float pressure = bme280.readPressure() / 100.0F;
        float humidity = bme280.readHumidity();
        printUart( "Sending BME readings: %f *C %f hPa %f %%", temperature, pressure, humidity );
        send( bme280Temp.set( temperature, 1 ) );
        send( bme280Press.set( pressure, 1 ) );
        send( bme280Hum.set( humidity, 1 ) );
      }
#endif
} // end of main loop.

void receive(const MyMessage &message) {
  // We only expect one type of message from controller. But we better check anyway.
  if( message.type == V_LIGHT ) {
    printUart( "Received update of %d sensor, new value %u", message.sensor, message.getBool() );
    // Switches are read only
    if( ( message.sensor >= SWITCH_MAX_ID ) &&
      ( message.sensor < m_lights_size ) ) {
      tLightSwitch* light = &m_lights[message.sensor];
      printUart( "Updating light relay %u %s pin: %u, new state: %u", message.sensor, light->description, light->pin, message.getBool() );
      light->currentState = message.getBool();
      light->message->set( light->currentState );
      printUart( "Sending confirmation of new state" );
      send( *light->message );
    }
   } 
}
