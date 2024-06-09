#ifndef BLUETOOTHCONTROL_H
#define BLUETOOTHCONTROL_H

#include <ESP32Servo.h>
#include "BluetoothSerial.h"

// Function declarations for Bluetooth control
void initializeBluetooth();
void handleBluetoothData();
void handleBluetoothCommand();

// Global variables related to Bluetooth
extern BluetoothSerial SerialBT;
extern int esc1Value, esc2Value, servo1Value;
extern bool moveServoLeft;
extern bool moveServoRight;

#endif
