
#include "peripherals/iot_config.h"


// Translate iot_configs.h defines into variables used by the sample
const char* hostname = "IED-ESP32-DEVICE";
const char* ssid = IOT_CONFIG_WIFI_SSID;
const char* password = IOT_CONFIG_WIFI_PASSWORD;
const char* host = IOT_CONFIG_IOTHUB_FQDN;
const char* mqtt_broker_uri = "mqtts://" IOT_CONFIG_IOTHUB_FQDN;
const char* device_id = IOT_CONFIG_DEVICE_ID;

// static const int mqtt_port = AZ_IOT_DEFAULT_MQTT_CONNECT_PORT;


// Control variables
unsigned long last = 0;