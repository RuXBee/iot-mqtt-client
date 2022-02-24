#include <WiFi.h>

#include "globals.h"
#include "peripherals/SerialLogger.h"


void connectToWiFi() {
    Logger.Info("Connecting to WIFI SSID " + String(ssid));

    WiFi.mode(WIFI_STA);
    WiFi.hostname(hostname);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");

    Logger.Info("WiFi connected, IP address: " + WiFi.localIP().toString());
}

