#include <Arduino.h>

const int buttonPin = 32; // SunFounder button module connected to GPIO32

void setup() {
    Serial.begin(115200);           // Open Serial Monitor
    pinMode(buttonPin, INPUT_PULLUP); // Internal pull-up resistor
    Serial.println("Button Test Started!");
}

void loop() {
    int buttonState = digitalRead(buttonPin);

    if(buttonState == LOW){ // Button pressed
        Serial.println("Button Pressed!");
    }

    delay(100); // Small debounce
}