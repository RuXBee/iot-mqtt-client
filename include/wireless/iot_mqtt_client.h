
#ifndef IOT_MQTT_CLIENT_H
#define IOT_MQTT_CLIENT_H

#include "PubSubClient.h"
#include <WiFi.h>




void mqtt_init_client(void);
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void mqtt_management(void);


#endif