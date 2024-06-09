#include "BluetoothControl.h"
#include "ServoControl.h"

// Arduino setup function, runs once at startup
void setup() {
    initializeBluetooth();  // Initialize Bluetooth communication
    initializeServos();     // Initialize servo motors
}

// Arduino loop function, runs repeatedly
void loop() {
    handleBluetoothData();  // Handle incoming Bluetooth data
    handleServoMovement();  // Handle servo motor movements
}
