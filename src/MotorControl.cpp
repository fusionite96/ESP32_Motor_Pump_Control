#include "MotorControl.h"
#include "Variables.h"
#include "LogManagement.h"
#include "WebServer.h"

bool motorRunning = false;
unsigned long motorStartTime = 0;
unsigned long motorRunDuration = 0;
String activeUser = "";

void start_motor(const String& user, int timer_minutes) {
    if (motorRunning) return;
    digitalWrite(MOTOR_PIN, HIGH);
    motorStartTime = millis();
    motorRunDuration = timer_minutes * 60 * 1000;
    motorRunning = true;
    activeUser = user;
    logMotorEvent("Motor Started", user, timer_minutes);
    broadcastMotorStatus(true, timer_minutes);
}

void stop_motor(const String& user) {
    if (!motorRunning) return;
    digitalWrite(MOTOR_PIN, LOW);
    motorRunning = false;
    String actor = (user == "ESP32") ? "ESP32" : activeUser;
    logMotorEvent("Motor Stopped", actor, motorRunDuration / 60000);
    broadcastMotorStatus(false, 0);
}

void checkMotorTimeout() {
    if (motorRunning && millis() - motorStartTime >= motorRunDuration) {
        stop_motor("ESP32");
    } else if (motorRunning && millis() - motorStartTime >= MAX_TIMER * 60 * 1000) {
        stop_motor("ESP32");
    }
}

bool isMotorRunning() {
    return motorRunning;
}
