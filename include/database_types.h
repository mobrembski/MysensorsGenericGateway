#ifndef DATABASE_TYPES_H
#define DATABASE_TYPES_H

#include <core/MyMessage.h>

typedef void (*tLongPressCallback)(void);

typedef struct {
  const uint8_t pin;
  const char* description;
  const uint8_t relayId;
  const mysensors_data_t datatype;
  const mysensors_sensor_t sensortype;
  const bool inactive;
#ifdef MCP23017_SUPPORT
  const uint8_t i2cAddress;
#endif
  tLongPressCallback longPressCallback;
  bool currentState;
  
  bool lastState;
  bool startTimeout;
  unsigned long buttonPressStartTimeStamp;
  unsigned long buttonPressDuration;
  MyMessage* message;
} tLightSwitch;

typedef struct {
  const uint8_t pin;
  const char* description;
#ifdef MCP23017_SUPPORT
  const uint8_t i2cAddress;
#endif
  bool currentState;
} tRelay;

#endif /* DATABASE_TYPES_H */