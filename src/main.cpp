// Main configuration is here:
#include "config.h"
#include "callbacks.h"
#include "database.h"

// LIBRARIES
#include <SPI.h>                                  // A communication backbone, the Serial Peripheral Interface.
#include <Ethernet.h>                             // Ethernet library
#include <MySensors.h>                            // The MySensors library. Hurray!
#include <Wire.h>                                 // Enables the Wire communication protocol.
#include <Bounce2.h>

#define MAX_UART_BUF_LEN          100             // UART Maxium buffer length
#define DEBOUNCE_INTERVAL         25              // Debounce interval in ms
#define PERIODIC_LIGHT_SEND       1               // Send light states periodically? 1 = Yes, 0 = No, only when switch change.
#define PERIODIC_LIGHT_INTERVAL   10000           // Interval between Light sends, button press is always send immediately

#define noEvent                   0               // Return value for checkButton when no event occurs
#define shortPress                1               // Return value for checkButton when short press occurs
#define longPress                 2               // Return value for checkButton when long press occurs
#define shortTime                 250             // Button press time in ms for short press
#define longTime                  800             // Button press time in ms for long press


static Bounce debouncers[SWITCH_MAX_ID];
static char uartBuffer[MAX_UART_BUF_LEN];
unsigned long m_lights_send_interval = PERIODIC_LIGHT_INTERVAL;

void printUart( const char *format, ...) {
  va_list args;
  va_start( args, format );
  vsprintf( uartBuffer, format, args );
  Serial.print( uartBuffer );
  Serial.print( "\n" );
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
      debouncers[i].attach( light->pin );
      debouncers[i].interval( DEBOUNCE_INTERVAL );
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

void setup() {
  Wire.begin(); // Wire.begin(sda, scl) // starts the wire communication protocol, used to chat with the BME280 sensor.
  Serial.begin(115200); // for serial debugging over USB.
  printUart("Hello %s!", MY_HOSTNAME );
  configurePins();
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

byte checkButton(tLightSwitch* light, Bounce* button)
{
  byte event = noEvent;
  // Update the Bounce instance, does digitalRead of button
  button->update();

  // Button press transition from LOW to HIGH)
  if (button->rose())
  {
    printUart("Rose");
    light->buttonPressStartTimeStamp = millis();
    light->startTimeout = true;
  }

  // Button release transition from HIGH to LOW) :
  if (button->fell())
  {
    printUart("fell");
    light->buttonPressDuration = (millis() - light->buttonPressStartTimeStamp);
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
        digitalWrite(relay->pin, relay->currentState);
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
      tRelay* relay = &m_relays[light->relayId];
      Bounce* debouncer = &debouncers[i];
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
          break;
      }
#ifdef STANDALONE_MODE
      switchRelayForLight(relay, light);
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
