#undef MY_TRANSPORT_SANITY_CHECK
#define MY_TRANSPORT_UPLINK_CHECK_DISABLED
// if you uncomment this, you can get test and debug updates about everything the sensor is doing by using the serial monitor tool.
#define MY_DEBUG
//#define MY_DEBUG_OTA

#define MY_GATEWAY_SERIAL
//#define MY_GATEWAY_W5100
//#define MY_GATEWAY_MQTT_CLIENT
#define MY_HOSTNAME "MySensorsTest2-Relay1"
#define SKETCH_VERSION "1.3"
//#define USE_STATIC_IP // Uncomment, if you don't want to use DHCP

#ifdef USE_STATIC_IP
#define MY_IP_ADDRESS 192,168,8,35          // Static IP Address
#define MY_IP_SUBNET_ADDRESS 255,255,255,0  // IP Netmask
#define MY_IP_GATEWAY_ADDRESS 192,168,8,1   // Internet (not MQTT) gateway address
#endif /* USE_STATIC_IP */

#ifdef MY_GATEWAY_MQTT_CLIENT
#define MY_MAC_ADDRESS 0x00, 0x08, 0xDC, 0xAA, 0xBB, 0x01
// Set this node's subscribe and publish topic prefix
#define MY_MQTT_PUBLISH_TOPIC_PREFIX "mysensorsTest2-out"
#define MY_MQTT_SUBSCRIBE_TOPIC_PREFIX "mysensorsTest2-in"

// Set MQTT client id
#define MY_MQTT_CLIENT_ID "mysensors-relayTest"
// MQTT broker ip address or url. Define one or the other.
//#define MY_CONTROLLER_URL_ADDRESS "m20.cloudmqtt.com"
#define MY_CONTROLLER_IP_ADDRESS 192, 168, 8, 32
//
//// The MQTT broker port to to open
#define MY_PORT 1883
#define MY_MQTT_USER "mqtt"
#define MY_MQTT_PASSWORD "666mqtt"
// Dla SPI - 10,50, 51, 52 - trzeba zaaktualizować
#define MY_W5100_SPI_EN 10
#endif /* MY_GATEWAY_MQTT_CLIENT */

#define STANDALONE_MODE