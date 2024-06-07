#include <ESP32Servo.h>
#include "BluetoothSerial.h"
// const char *pin = "1234"; 
String device_name = "ESP32-BT-Slave";
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif
BluetoothSerial SerialBT;


String numericPart = "";
char codeReceived;

void setup() {
    Serial.begin(115200);
    SerialBT.begin(device_name); 
}

void loop() {
    if (Serial.available()) {
        SerialBT.write(Serial.read());
    }
    while (SerialBT.available() > 0) {
        String line = SerialBT.readStringUntil('\n');
        numericPart = "";
        for (int i = 0; i < line.length(); i++) {
            int character = line[i];
            if (isDigit(character)) {
                numericPart += (char) character;
            } else if (character != '\n') {
                codeReceived = character;
            } else {
                break;
            }
        }
    }
  
    switch (codeReceived) {
        //Add or delete as per need
        case 'F': goForward(); break;//control BLDC1
        case 'L': turnLeft(); break //change servo angle
        //case 'B': goBack(); break;
        case 'R': turnRight(); break; //change servo angle
        case 'S': stop(); break;
      /*
        case 'M': set_1(); break;
        case 'm': set_2(); break;
        case 'N': set_3(); break;
        case 'n': set_4(); break;
      */
        case 'T'://control thruster speed
            if (numericPart != "") {
                thrusterSpeed(numericPart.toInt());
            }
            break;
        case 'K'://control lift motor speed
            if (numericPart != "") {
                liftSpeed(numericPart.toInt());
            }
            break;
    }
    delay(5);
}
