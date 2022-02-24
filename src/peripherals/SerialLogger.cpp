// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#include "peripherals/SerialLogger.h"
#include <time.h>


const char* ntpServer = "pool.ntp.org";
const int  gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

String get_time_utc() {
  
  struct tm* ptm;
  time_t now = time(NULL);

  ptm = gmtime(&now);

  String datetime = String(ptm->tm_year+UNIX_EPOCH_START_YEAR) + "-" + String(ptm->tm_mon) + "-" + String(ptm->tm_mday) + "T" + String(ptm->tm_hour) + ":" + String(ptm->tm_min) + ":" + String(ptm->tm_sec) + "Z";
  return datetime;
}


SerialLogger::SerialLogger() { Serial.begin(SERIAL_LOGGER_BAUD_RATE); }

void SerialLogger::Info(String message) {
  
  Serial.print(get_time_utc() + " [INFO] ");
  Serial.println(message);
}

void SerialLogger::Error(String message) {
  Serial.print(get_time_utc()  + " [ERROR] ");
  Serial.println(message);
}

void SerialLogger::Warning(String message) {
  Serial.print(get_time_utc()  + " [WARNING] ");
  Serial.println(message);
}

SerialLogger Logger;