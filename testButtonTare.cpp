#include <Arduino.h>

const int sensorPin = A0;    // Photoresistor
const int tareButton = 32;   // Button to tare
int tareOffset = 0;          // Current tare offset

void setup() {
    Serial.begin(115200);
    pinMode(sensorPin, INPUT);
    pinMode(tareButton, INPUT_PULLUP); // Button with internal pull-up
    Serial.println("Tare Test Started!");
}

void loop() {
    // Check if tare button is pressed
    if(digitalRead(tareButton) == LOW){
        tareOffset = analogRead(sensorPin); // Set new tare
        Serial.print("Tare pressed! New offset = ");
        Serial.println(tareOffset);
        delay(300); // debounce
    }

    // Read sensor and apply tare
    int sensorValue = analogRead(sensorPin) - tareOffset;

    Serial.print("Tared Sensor Value: ");
    Serial.println(sensorValue);

    delay(500); // Update twice per second
}