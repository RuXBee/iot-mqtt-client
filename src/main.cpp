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
	preferences.begin("credentials", false);
	
	connectToWiFi();
	delay(10);
	mqtt_init_client();
	configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
	delay(2000);
	Logger.Info("Start program");

}

void loop() {

	if (millis() > (last + 1000)) {
		last = millis();
		mqtt_management();
	}
}
