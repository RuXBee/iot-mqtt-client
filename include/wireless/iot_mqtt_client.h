
#ifndef IOT_MQTT_CLIENT_H
#define IOT_MQTT_CLIENT_H

#include "PubSubClient.h"

// Global variables
// extern const char * clientId;
extern unsigned long last;

// Global mqtt client
extern PubSubClient mqtt_client;

enum {
    MQTT_MACHINE_DEFAULT,
    ERASE_WIFI,
    RESET_DEVICE,
    SWITCH_LED,
};

void updateConfigCallback();
void readConfig();


void auto_wifi_manager(void);

void mqtt_init_client(void);
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void mqtt_management(void);
void sendJsonMqtt(const char *payload);


#endif // IOT_MQTT_CLIENT_H