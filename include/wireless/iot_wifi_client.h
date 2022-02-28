

#ifndef IOT_WIFI_CLIENT_H
#define IOT_WIFI_CLIENT_H

#include <WiFiManager.h>

extern WiFiManager wifiManager;

void connectToWiFi(void);
void auto_wifi_manager(void);

#endif // IOT_WIFI_CLIENT_H
