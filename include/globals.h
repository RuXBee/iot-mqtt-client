
#ifndef GLOBALS_H
#define GLOBALS_H


// Translate iot_configs.h defines into variables used by the sample
extern const char* hostname;
extern const char* ssid;
extern const char* password;
extern const char* host;
extern const char* mqtt_broker_uri;
extern const char* device_id;

// static const int mqtt_port = AZ_IOT_DEFAULT_MQTT_CONNECT_PORT;


// Control variables
extern unsigned int last;

#endif // GLOBALS_H