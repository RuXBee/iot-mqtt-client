
#ifndef IOT_MQTT_CLIENT_H
#define IOT_MQTT_CLIENT_H

#include "PubSubClient.h"


extern unsigned long last;
// Global mqtt client
extern PubSubClient mqtt_client;

void updateConfigCallback();
void readConfig();

void auto_wifi_manager(void);

void mqtt_init_client(void);
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void mqtt_management(void);
void sendJsonMqtt(void);


#endif // IOT_MQTT_CLIENT_H