/*
   config.h

   Copyright(c) 2021 Michał Obrembski <michal.o@szerszen.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; If not, see <http://www.gnu.org/licenses/>.
*/

#undef MY_TRANSPORT_SANITY_CHECK
#define MY_TRANSPORT_UPLINK_CHECK_DISABLED
// if you uncomment this, you can get test and debug updates about everything the sensor is doing by using the serial monitor tool.
#define MY_DEBUG
//#define MY_DEBUG_OTA
#define MYSENSORS_DEBUG_PREFIX "0;255;3;0;9;"

#define MY_GATEWAY_SERIAL
//#define MY_GATEWAY_W5100
//#define MY_GATEWAY_MQTT_CLIENT
#define MY_HOSTNAME "MySensorsMainGW"
#define SKETCH_VERSION "1.3"
//#define USE_STATIC_IP // Uncomment, if you don't want to use DHCP
#define MY_NODE_ID 1

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
// For EasySwitch Mega Board SPI_EN - 10, 50, 51, 52
#define MY_W5100_SPI_EN 10
#endif /* MY_GATEWAY_MQTT_CLIENT */

/* Standalone mode means that device will switch the light without waiting for response from HA. */
#define STANDALONE_MODE
/* Uncomment if you wish to add MCP GPIO I2C adapters support */
#define MCP23017_SUPPORT
/* Uncomment if you wish to add BME280 support */
//#define BME280_SUPPORT
/* Uncomment if you wish to scan I2C Bus for devices on startup */
#define I2C_SCANNER_SUPPORT

/* Uncomment if you want to use database for development board */
//#define DEVELOPER_BOARD