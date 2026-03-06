#include <Arduino.h>

const int sensorPin = A0; // The photoresistor module pin was connected to the A0 pin in the ESP32
const int touchPin = A1; // The touch module signal pin was connected to the A1 pin in the ESP32
const int G = 12; // The traffic light LED pin G (for the green light) was connected to the D12 pin in the ESP32
const int Y = 27; // The traffic light LED pin Y (for the yellow light) was connected to the D27 pin in the ESP32
const int R = 33; // The traffic light LED pin R (for the red light) was connected to the D33 pin in the ESP32

void setup() {
    pinMode(sensorPin, INPUT); // This defines the photoresistor signal pin as input
    pinMode(touchPin, INPUT); // This defines the touch signal pin as input
    pinMode(G, OUTPUT); // This defines the pin G as output
    pinMode(Y, OUTPUT); // This defines th pin Y as output
    pinMode(R, OUTPUT); // This defines the pin R as output
    Serial.begin(115200); // This initializes Serial communication
}

void loop() {
    // If the photoresistor recognizes low light (night time), the yellow traffic light will blink to signal yield at the intersection during night time
    if (analogRead(sensorPin) >= 2250) {
        Serial.println("Nighttime Flashing Yellow Light");  // Prints out context information of what the code is doing
        digitalWrite(G,LOW); // The green light is turned off
        digitalWrite(Y,HIGH); // The yellow light is turned on
        digitalWrite(R,LOW); // The red light is turned off
        delay(500); // The yellow light remains on for 0.5 seconds (500 ms)

        digitalWrite(G,LOW); // The green light is turned off
        digitalWrite(Y,LOW); // The yellow light is turned off
        digitalWrite(R,LOW); // The red light is turned off
        delay(500); // All the lights are turned off for 0.5 seconds
    }
    // If the photoresistor recognizes medium to high light (daytime), the intersection will follow regular daytime traffic light green to yellow to red.
    else if (analogRead(sensorPin) <= 1200 && analogRead(touchPin) < 1500) {
        Serial.println("Daytime Regular Traffic Light");  // Prints out context information of what the code is doing
        digitalWrite(G,HIGH); // The green light is turned on
        digitalWrite(Y,LOW); // The yellow light is turned off
        digitalWrite(R,LOW); // The red light is turned off
        delay(4000); // The green light remains on for 4 seconds (4000 ms)

        digitalWrite(G,LOW); // The green light is turned off
        digitalWrite(Y,HIGH); // The yellow is turned on
        digitalWrite(R,LOW); // The red light is turned off
        delay(1000); // The yellow light remains on for 1 second (1000 ms)

        digitalWrite(G,LOW); // The green light is turned off
        digitalWrite(Y,LOW); // The yellow light is turned off
        digitalWrite(R,HIGH); // The red light is turned on
        delay(3000); // The red light remains on for 3 seconds (3000 ms)
    }
    // If the touch module recognizes touch (pedestrian button pressed), the intersection traffic light will turn red and crosswalk sign will turn on for all pedestrians
    else if (analogRead(sensorPin) <= 1200 && analogRead(touchPin) > 1500) {
        Serial.println("Crosswalk sign On for all Pedestrians");  // Prints out context information of what the code is doing

        digitalWrite(G,LOW); // The green light is turned off
        digitalWrite(Y,LOW); // The yellow light is turned off
        digitalWrite(R,HIGH); // The red light is turned on
        delay(5000); // The red light remains on for 5 seconds (5000 ms)
    }
}