#ifndef SERVOCONTROL_H
#define SERVOCONTROL_H

#include <ESP32Servo.h>

// Function declarations for servo control
void initializeServos();
void handleServoMovement();
void calibrateESC(Servo& esc);

// Global variables related to servos
extern Servo esc1;
extern Servo esc2;
extern Servo servo1;
extern unsigned long lastServoMoveTime;

#endif
