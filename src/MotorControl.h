#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
#include <Arduino.h>
void start_motor(const String& user, int timer_minutes);
void stop_motor(const String& user);
void checkMotorTimeout();
bool isMotorRunning();
#endif
