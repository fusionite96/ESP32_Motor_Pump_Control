
#ifndef LOG_MANAGEMENT_H
#define LOG_MANAGEMENT_H

#include <Arduino.h>

void initLogSystem();
void logMotorEvent(const String& action, const String& user, int timer_value);
String getFormattedLogs();
void handleSessionTimeouts();
void cleanOldLogs();

#endif
