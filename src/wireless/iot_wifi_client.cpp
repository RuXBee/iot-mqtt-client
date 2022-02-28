
#include <WiFi.h>
#include "globals.h"
#include "peripherals/SerialLogger.h"
#include "wireless/iot_wifi_client.h"

void connectToWiFi() {
    Logger.Info("Connecting to WIFI SSID " + String(ssid));

    WiFi.mode(WIFI_STA);
    WiFi.hostname(device_id);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");

    Logger.Info("WiFi connected, IP address: " + WiFi.localIP().toString());
}


WiFiManager wifiManager;

void auto_wifi_manager() {

    if(!wifiManager.autoConnect(device_id, password)) {
        Logger.Warning("FAiled connect WiFi...");
        delay(2000);
        ESP.restart();
    }
}
