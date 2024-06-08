#include <BluetoothSerial.h>
#include <DabbleESP32.h>
#include <ESP32Servo.h>

#define LED_PIN 10

BluetoothSerial SerialBT;

Servo esc1;  // create servo object to control the ESC
Servo esc2;
Servo servo1;

int esc1Value, esc2Value, servo1Value;

void setup() {
  Serial.begin(115200); // Use a higher baud rate for ESP32
  SerialBT.begin("ESP32Hovercraft"); // Bluetooth device name
  Dabble.begin(SerialBT);
  
  esc1.attach(7);
  esc2.attach(6);
  servo1.attach(5);
  pinMode(LED_PIN, OUTPUT);

  // ESC Calibration
  calibrateESC(esc1);
  calibrateESC(esc2);
}

void loop() {
  Dabble.processInput(); // Process data from Dabble app

  // Controlling servos
  int j2PotX = GamePad.getJoystickValue(1, 1); // Get Joystick 2 X value
  servo1Value = map(j2PotX, -512, 512, 0, 50);
  servo1.write(servo1Value);

  // Controlling brushless motor with ESC
  // Lift propeller
  int pot1 = GamePad.getSliderValue(1); // Get Slider 1 value
  esc1Value = map(pot1, 0, 255, 1000, 2000); // Map the receiving value from 0 to 255 to 1000 to 2000, values used for controlling ESCs
  esc1.writeMicroseconds(esc1Value); // Send the PWM control signal to the ESC

  // Thrust propeller
  int j1PotY = GamePad.getJoystickValue(1, 2); // Get Joystick 1 Y value
  esc2Value = constrain(j1PotY, -512, 512); // Joysticks stay in the middle. So we only need the upper values from 130 to 255
  esc2Value = map(esc2Value, -512, 512, 1000, 2000);
  esc2.writeMicroseconds(esc2Value);

  // Monitor the battery voltage
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (3.3 / 4095.0) * 3; // Convert the reading values from 3.3v to suitable 12V, adjust if necessary for your voltage divider
  Serial.println(voltage);
  // If voltage is below 11V, turn on the LED
  if (voltage < 11) {
    digitalWrite(LED_PIN, HIGH);
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }
}

void calibrateESC(Servo& esc) {
  // Send maximum signal to ESC
  esc.writeMicroseconds(2000);
  delay(2000); // wait for 2 seconds

  // Send minimum signal to ESC
  esc.writeMicroseconds(1000);
  delay(2000); // wait for 2 seconds
}

void resetData() {
  // Reset the values when there is no radio connection - Set initial default values
  // No need for resetData function in this case since Dabble will handle reconnections automatically
}
