#include <Arduino.h>

const int touchPin = A1; // The touch module signal pin was connected to the A1 pin in the ESP32

void setup() {
  Serial.begin(115200); // This initializes Serial communication
  pinMode(touchPin, INPUT); // This defines the touch signal pin as input
}

void loop() {
    int touchValue = analogRead(touchPin); // // This line reads the value from the touch module sensor
    // If the touch module sensor detects a value greater than 2000 (touch detected):
    if (touchValue > 2000) {
        Serial.println("Crosswalk sign On for all Pedestrians"); // Prints out context information of what the code is doing
    }
    // If the touch module sensor detects a value smaller than 2000 (no touch detected):
    else {
        Serial.println("Green light for drivers"); // Prints out context information of what the code is doing
    }
}
