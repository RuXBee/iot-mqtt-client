#include <Arduino.h>
#include <WiFi.h>
#include <time.h>
#include <Preferences.h>

#include "globals.h"
#include "peripherals/SerialLogger.h"
#include "wireless/iot_wifi_client.h"
#include "wireless/iot_mqtt_client.h"





Preferences preferences;


void setup() {
	delay(100);
    // wifiManager.erase(true);
	// Logger.Info("Erase WiFi manager");

	preferences.begin("credentials", false);
	
	// connectToWiFi();
	auto_wifi_manager();
	delay(10);
	mqtt_init_client();
	configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
	delay(2000);
	Logger.Info("MQTT client initialize");

}

void loop() {

	if (millis() > (last + 1000)) {
		last = millis();
		mqtt_management();
	}
}
