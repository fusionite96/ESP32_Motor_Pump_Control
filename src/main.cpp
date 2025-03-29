#include <Arduino.h>
#include "WebServer.h"
#include "MotorControl.h"
#include "UserManagement.h"
#include "LogManagement.h"
#include "Variables.h"

unsigned long lastActivityTime = 0;

void resetInactivityTimer() {
    lastActivityTime = millis();
}

void checkInactivityTimeout() {
    if ((millis() - lastActivityTime) > (INACTIVITY_TIMEOUT * 1000)) {
        handleSessionTimeouts();
        resetInactivityTimer();
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(MOTOR_PIN, OUTPUT);
    digitalWrite(MOTOR_PIN, LOW);
    initWebServer();
    initMotorControl();
    initUserManagement();
    initLogSystem();
    resetInactivityTimer();
    Serial.println("✅ ESP32 Water Pump Control initialized.");
}

void loop() {
    checkMotorTimeout();
    checkInactivityTimeout();
    handleWebSocket();
    delay(100);
}
