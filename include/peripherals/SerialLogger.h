// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#ifndef SERIALLOGGER_H
#define SERIALLOGGER_H

#include <Arduino.h>

#ifndef SERIAL_LOGGER_BAUD_RATE
#define SERIAL_LOGGER_BAUD_RATE 115200
#endif
#define UNIX_EPOCH_START_YEAR 1900

extern const char* ntpServer;
extern const int gmtOffset_sec;
extern const int daylightOffset_sec;

String get_time_utc(void);


class SerialLogger
{
public:
  SerialLogger();
  void Info(String message);
  void Error(String message);
  void Warning(String message);
};

extern SerialLogger Logger;




#endif // SERIALLOGGER_H