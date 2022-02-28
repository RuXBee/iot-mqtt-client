
#include "peripherals/credentials.h"


// Translate iot_configs.h defines into variables used by the sample

const char* ssid = IOT_CONFIG_WIFI_SSID;
const char* password = IOT_CONFIG_WIFI_PASSWORD;
const char* device_id = HOSTNAME;

// static const int mqtt_port = AZ_IOT_DEFAULT_MQTT_CONNECT_PORT;


// Control variables
unsigned long last = 0;