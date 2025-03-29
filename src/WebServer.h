
#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <Arduino.h>

void initWebServer();
void handleWebSocket();
void broadcastMotorStatus(bool isRunning, int timer_value);

#endif
