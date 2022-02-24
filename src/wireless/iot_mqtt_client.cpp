#include "PubSubClient.h"
#include <WiFi.h>
#include "peripherals/SerialLogger.h"

// MQTT CLIENT
const char *mqtt_server = "";
const uint16_t mqtt_port = 1883;
const char *mqtt_user = "";
const char *mqtt_pass = "";
const char *root_topic_subscribe = "/#";
const char *root_topic_publish = "/output";

WiFiClient espClient;
PubSubClient client(espClient);
char msg[25];
long count;


void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
    String incoming = "";
    String concaten_print = "";
    concaten_print = "Available message from -> " + String(topic);
    Logger.Info(concaten_print);
    for (int i = 0; i < length; i++) {
        incoming += (char)payload[i];
    }
    incoming.trim();
    if ((String(topic) == "/reset")&&(incoming == "reset")) {
        ESP.restart();
    }
    Logger.Info("Topic: " + String(topic) + "| Message: " + incoming);
}

void mqtt_init_client() {
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(mqtt_callback);
    client.loop();
}

/*
This function will execute every principal timer period of program
*/
void mqtt_management() {

    client.loop();

    if (!client.connected()) {
        Logger.Warning("Trying to connect mqtt broker...");
        // Random client ID
        String clientId = "ESP32_DEVICE_";
        clientId += String(random(0xffff), HEX);
        // Try to connect
        if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
            Logger.Info("Connected to: " + String(mqtt_user));
            // Subscribes different topics
            if (client.subscribe(root_topic_subscribe)) {
                Logger.Info("Subscribed in topic: " + String(root_topic_subscribe));
            } else {
                Logger.Error("MQTT error topic subscribed");
            }
        } else {
            Logger.Error("MQTT error code: " + String(client.state()));
        }
    }
}



