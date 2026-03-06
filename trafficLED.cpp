#include <Arduino.h>

const int G = 12; // The traffic light LED pin G (for the green light) was connected to the D12 pin in the ESP32
const int Y = 27; // The traffic light LED pin Y (for the yellow light) was connected to the D27 pin in the ESP32
const int R = 33; // The traffic light LED pin R (for the red light) was connected to the D33 pin in the ESP32

void setup() {
    pinMode(G, OUTPUT); // This defines the pin G as output
    pinMode(Y, OUTPUT); // This defines th pin Y as output
    pinMode(R, OUTPUT); // This defines the pin R as output
    Serial.begin(115200); // This initializes Serial communication
}

void loop () {
    digitalWrite(G,HIGH); // The green light is turned on
    digitalWrite(Y,LOW); // The yellow light is turned off
    digitalWrite(R,LOW); // The red light is turned off
    delay(500); // The green light remains on for 0.5 seconds (500 ms)

    digitalWrite(G,LOW); // The green light is turned off
    digitalWrite(Y,HIGH); // The yellow light is turned on
    digitalWrite(R,LOW); // The red light is turned off
    delay(500); // The yellow light remains on for 0.5 seconds (500 ms)

    digitalWrite(G,LOW); // The green light is turned off
    digitalWrite(Y,LOW); // The yellow light is turned off
    digitalWrite(R,HIGH); // The red light is turned on
    delay(500); // The red light remains on for 0.5 seconds (500 ms)

    digitalWrite(G,LOW); // The green light is turned off
    digitalWrite(Y,LOW); // The yellow light is turned off
    digitalWrite(R,LOW); // The red light is turned off
    delay(500); // All the lights are turned off for 0.5 seconds (500 ms) before the loop starts again
}