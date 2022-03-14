#include <Arduino.h>
#include "peripherals/SerialLogger.h"
#include "wireless/iot_mqtt_client.h"


void setup() {
	
	delay(100);
	readConfig();
	auto_wifi_manager();
	delay(10);
	mqtt_init_client();
	configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
	delay(1000);
	Logger.Info("MQTT client initialize");

}

void loop() {

	if (millis() > (last + 2000)) {
		last = millis();
		mqtt_management();
	    const char *payload = "{\"deviceId\": \"ESP32\"}";
		sendJsonMqtt(payload);
	}
}
