#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Interface Prototype 2: This prototype tested the button module for tare button on top of testing photoresistor, touch module, LED, and LCD
// NOT WORKING AS INTENDED 

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C LCD address, 16 columns, 2 rows

const int sensorPin = A0; // The photoresistor module pin was connected to the A0 pin in the ESP32
const int touchPin = A1; // The touch module signal pin was connected to the A1 pin in the ESP32
const int G = 12; // The traffic light LED pin G (for the green light) was connected to the D12 pin in the ESP32
const int Y = 27; // The traffic light LED pin Y (for the yellow light) was connected to the D27 pin in the ESP32
const int R = 33; // The traffic light LED pin R (for the red light) was connected to the D33 pin in the ESP32
const int tareButton = 32; // GPIO32 for tare button
int tareOffset = 0; // Stores current weight based on the tared valued

void setup() {
    Wire.begin(22,20); // SDA, SCL for ESP32 connections

    lcd.init(); // This initializes LCD
    lcd.backlight(); // This turns on LCD backlight

    pinMode(sensorPin, INPUT); // This defines the photoresistor signal pin as input
    pinMode(touchPin, INPUT); // This defines the touch signal pin as input
    pinMode(tareButton, INPUT_PULLUP); // Use internal pull-up for button
    pinMode(G, OUTPUT); // This defines the pin G as output
    pinMode(Y, OUTPUT); // This defines th pin Y as output
    pinMode(R, OUTPUT); // This defines the pin R as output
    
    Serial.begin(115200); // This initializes Serial communication

    lcd.setCursor(0,0);
    lcd.print("System Ready");
}

void loop () {
    // Check if tare button is pressed
        if(digitalRead(tareButton) == LOW){
            tareOffset = analogRead(sensorPin); // store current value as tare
            Serial.print("Tare pressed! New offset = ");
            Serial.println(tareOffset);
            delay(300); // debounce
        }
        // Read sensor and apply tare
        int potValue = analogRead(sensorPin) - tareOffset; // subtract tare

   // If there is a container on top of the scale but RFID is not detected:
   // Input: Touch sensor is activated (Something is placed on top of the scale)
   // Output: Yellow blinking light
   // Output: Message on the LCD screen alternates with weight displayed
        // Changes that need to be made:
        // Add condition that RFID is not detected
        // See if you can make the light remain on even after the container is removed from the scale until the user taps a RFID sticker
    if (analogRead(touchPin) > 1500) {
        Serial.println("Weight Not Stored! Remember to tap the RFID Tag!");  // Prints out context information of what the code is doing

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Tap RFID Tag!");
        lcd.setCursor(0,1);
        lcd.print("Weight Not Saved");
        delay(1000);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Tap RFID Tag!");
        lcd.setCursor(0,1);
        lcd.print(potValue); // Print the value for the photoresistor
        lcd.setCursor(15,1);
        lcd.print("g"); // Print gram units to the last column in the row where the value is being printed
        delay(1000);

        digitalWrite(G,LOW); // The green light is turned off
        digitalWrite(Y,HIGH); // The yellow light is turned on
        digitalWrite(R,LOW); // The red light is turned off
        delay(250); // The yellow light remains on for 0.5 seconds (500 ms)

        digitalWrite(G,LOW); // The green light is turned off
        digitalWrite(Y,LOW); // The yellow light is turned off
        digitalWrite(R,LOW); // The red light is turned off
        delay(250); // All the lights are turned off for 0.5 seconds
    }
    // If the ingredient is below the threshold:
    // Input: Sensor detects a value that is below the threshold (currently using photoresistor value)
    // Output: Red Blinking light
    // Output: Message on the LCD screen alternates with weight displayed
        // Changes that need to be made:
        // Instead of using photoresistor values, we need to use the scale values.
    else if (potValue < 500) {
        Serial.println("Ingredient Weight is Below Threshold!");
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Weight Low!");
        lcd.setCursor(0,1);
        lcd.print("Refill Needed");
        delay(1000);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Weight Low!");
        lcd.setCursor(0,1);
        lcd.print(potValue); // Print the value for the photoresistor
        lcd.setCursor(15,1);
        lcd.print("g"); // Print gram units to the last column in the row where the value is being printed
        delay(1000);

        digitalWrite(G,LOW); // The green light is turned off
        digitalWrite(Y,LOW); // The yellow light is turned off
        digitalWrite(R,HIGH); // The red light is turned on
        delay(250); // The red light remains on for 0.5 seconds (500 ms)

        digitalWrite(G,LOW); // The green light is turned off
        digitalWrite(Y,LOW); // The yellow light is turned off
        digitalWrite(R,LOW); // The red light is turned off
        delay(250); // All the lights are turned off for 0.5 seconds
    }
    // Normal conditions:
    // Output: Green Light remains on
    // Output: Only weight is displayed on the LCD screen
    else {
        digitalWrite(G,HIGH); // The green light is turned on
        digitalWrite(Y,LOW); // The yellow light is turned off
        digitalWrite(R,LOW); // The red light is turned off
        delay(500); // The green light remains on for 0.5 seconds (500 ms)

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Weight:");
        lcd.setCursor(0,1);
        lcd.print(potValue); // Print the value for the photoresistor
        lcd.setCursor(15,1);
        lcd.print("g"); // Print gram units to the last column in the row where the value is being printed
    }
}