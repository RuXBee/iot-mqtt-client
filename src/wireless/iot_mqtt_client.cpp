#include <Arduino.h>
#include "WiFiManager.h"
#include "PubSubClient.h"
#include "WiFi.h"
#include "Preferences.h"
#include "ArduinoJson.h"
#include "peripherals/credentials.h"
#include "peripherals/SerialLogger.h"
#include "wireless/iot_mqtt_client.h"


// =======================================
// =======================================
// No volatile memory
// =======================================
// =======================================
// Memory variables
String clientId = DEFAULT_CLIENT;                               // Client ID
String deviceId = DEFAULT_DEVICE;                               // Device ID
unsigned long last = 0;                                         // Control principal infinite loop
static Preferences preferences;                                 // R/W flash memory

void readConfig() {

	preferences.begin("Config", true);
    // preferences.clear();
    clientId = preferences.getString("client", clientId);
    deviceId = preferences.getString("device", deviceId);
    preferences.end();
}



// =======================================
// =======================================
// WiFi manager
// =======================================
// =======================================
// WiFi manager variables
static WiFiManager wm;
static WiFiManagerParameter client_wifi("clientId", "Enter Client ID", clientId.c_str(), 50);
static WiFiManagerParameter device_wifi("deviceId", "Enter Device ID", deviceId.c_str(), 50);


// Callback when user enter WiFi credentials
void updateConfigCallback() {

    clientId = client_wifi.getValue();
    deviceId = device_wifi.getValue();
    preferences.begin("Config",false);
    preferences.putString("client", clientId);
    preferences.putString("device", deviceId);
    preferences.end();
    // ESP.restart();
}

void auto_wifi_manager() {

    wm.addParameter(&client_wifi);
    wm.addParameter(&device_wifi);
    // Handle changes
    wm.setSaveParamsCallback(updateConfigCallback);

    client_wifi.setValue(clientId.c_str(), sizeof(clientId));
    device_wifi.setValue(deviceId.c_str(), sizeof(deviceId));

    String name = deviceId + "__" + String(WiFi.macAddress());
    
    if (!wm.autoConnect(name.c_str(), "12345678")) {
        Logger.Warning("Failed connect WiFi...");
        delay(5000);
        ESP.restart();
    }
}



// =======================================
// =======================================
// MQTT Protocol
// =======================================
// =======================================
// MQTT CLIENT CONNECTION PARAMETERS
const char *mqtt_server = "15.188.173.233";                     // MQTT public IP
const uint16_t mqtt_port = 1883;                                // MQTT port
const char *mqtt_user = "ruben";                                // MQTT Broker user 
const char *mqtt_pass = "1234";                                 // MQTT Broker password
const char *root_topic_subscribe = "broker/";                   // MQTT subscribe topic
const char *root_topic_publish = "pub/";                        // MQTT publisher topic --> clientId/deviceId 

const byte led_pin = 13;
static WiFiClient espClient;
PubSubClient mqtt_client(espClient);



void mqtt_callback(char *, byte *, unsigned int);

void mqtt_init_client() {

    mqtt_client.setServer(mqtt_server, mqtt_port);
    mqtt_client.setCallback(mqtt_callback);
    mqtt_client.loop();
}

void mqtt_callback(char *topic, byte *payload, unsigned int length) {

    String incoming;
    for (int i = 0; i < length; i++) {
        incoming += (char)payload[i];
    }
    
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc,incoming);
    if (error) {
        Logger.Warning("deserializeJson failed " + String(error.f_str()));
        return;
    }

    String device = doc["deviceId"];
    bool reset = doc["data"]["reset"];
    bool default_wifi = doc["data"]["default_wifi"];
    bool led_state = doc["data"]["led_state"];

    if (device != deviceId) {

        String targetTopic = deviceId.c_str() + String("/") + clientId.c_str();
        Serial.println(reset);

        if (reset) ESP.restart();;
        if (default_wifi) wm.erase();
        // Write LED state
        digitalWrite(led_pin, led_state);
    }
}

/*
This function will execute every principal timer period of program
*/
void mqtt_management() {

    mqtt_client.loop();

    if (!mqtt_client.connected()) {
        Logger.Warning("Trying to connect mqtt broker...");
        // Random client ID
        String clientId = String(WiFi.macAddress());
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


void sendJsonMqtt(void) {


    static int temperature = 20;
    static int humidity = 50;
    StaticJsonDocument<1024> doc;
    
    // Simulate data
    if (++temperature > 40) temperature = 20;
    if (++humidity > 80) humidity = 30;

    String datetime = get_time_utc();

    char json[1024];
    sprintf(json, "{\"datetime\": \"%s\", \"deviceId\": \"%s\", \"data\": {\"temperature_grades\": %d, \"absolute_humidity\": %d} }", datetime.c_str(), deviceId.c_str(), temperature, humidity);

    String topic = clientId.c_str() + String("/");
    Logger.Info("SEND MESSAGE: " + String(json) +  " -- with topic: " + topic);
    mqtt_client.publish(topic.c_str(), json);
}

