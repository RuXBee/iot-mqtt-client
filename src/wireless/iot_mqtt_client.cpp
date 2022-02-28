#include "peripherals/SerialLogger.h"
#include "wireless/iot_mqtt_client.h"
#include "globals.h"

// MQTT CLIENT CONNECTION PARAMETERS
const char *mqtt_server = "15.188.173.233";                     // MQTT public IP
const uint16_t mqtt_port = 1883;                                // MQTT port
const char *mqtt_user = "ied-device";                           // MQTT Broker user 
const char *mqtt_pass = "12";                                 // MQTT Broker password
const char *root_topic_subscribe = "/#";                        // MQTT subscribe topic
const char *root_topic_publish = "/output";                     // MQTT publisher topic

WiFiClient espClient;
PubSubClient mqtt_client(espClient);

void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
    String incoming = "";
    String concaten_print = "";
    for (int i = 0; i < length; i++) {
        incoming += (char)payload[i];
    }
    incoming.trim();
    // Reset ESP32
    if ((String(topic) == "/reset")&&(incoming == "reset")) {
        ESP.restart();
    }
    
    Logger.Info("Topic: \"" + String(topic) + "\"   |   Msg: " + incoming);
}

void mqtt_init_client() {
    mqtt_client.setServer(mqtt_server, mqtt_port);
    mqtt_client.setCallback(mqtt_callback);
    mqtt_client.loop();
}

/*
This function will execute every principal timer period of program
*/
void mqtt_management() {

    mqtt_client.loop();

    if (!mqtt_client.connected()) {
        Logger.Warning("Trying to connect mqtt broker...");
        // Random client ID
        String clientId = device_id;
        clientId += String(random(0xffff), HEX);
        // Try to connect
        if (mqtt_client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
            Logger.Info("Connected to: " + String(mqtt_user));
            // Subscribes different topics
            if (mqtt_client.subscribe(root_topic_subscribe)) {
                Logger.Info("Subscribed in topic: " + String(root_topic_subscribe));
            } else {
                Logger.Error("MQTT error topic subscribed");
            }
        } else {
            Logger.Error("MQTT error code: " + String(mqtt_client.state()));
        }
    }
}



