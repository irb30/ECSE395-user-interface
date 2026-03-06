#include <Arduino.h>

// The photoresistor module pin was connected to the A0 pin in the ESP32
const int sensorPin = A0;

void setup() {
    // This initializes Serial communication
    Serial.begin(115200);
}

void loop() {
    // This line prints out the value from the photoresistor sensor
    Serial.println(analogRead(sensorPin));
    delay(5000); // This code waits for 5 seconds (5000 ms) before it prints out the updated photoresistor value
}