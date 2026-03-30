#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

// Prototype 6: MVP
// Remove photoresistor and touch module
// Container Memory

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C LCD address, 16 columns, 2 rows

const int G = 12; // The traffic light LED pin G (for the green light) was connected to the D12 pin in the ESP32
const int Y = 27; // The traffic light LED pin Y (for the yellow light) was connected to the D27 pin in the ESP32
const int R = 33; // The traffic light LED pin R (for the red light) was connected to the D33 pin in the ESP32

const int tareButton = 32; // GPIO32 for tare button
int tareOffset = 0; // Stores current weight based on the tared valued
bool tareActive = false; // Tracks if tare is ON or OFF
bool lastButtonState = HIGH; // Previous button state

const int menuButton = 14; //GPIO14 for menu button
bool menuState = false; // false = normal screen, true = menu
bool lastMenuButtonState = HIGH; 

const int upButton = 13;    // Navigate up in menu
bool lastUpButtonState = HIGH;

const int tareCaptureButton = 15;  // Capture empty container weight
bool lastTareCaptureButtonState = HIGH;

const int powerButton = 4;  // GPIO 4
bool lastPowerButtonState = LOW;
bool screenOn = false;       // tracks LCD state

const int LOADCELL_DOUT_PIN = 21;
const int LOADCELL_SCK_PIN = 19;
float weight;

//Calibration Function
const float SLOPE = -2.4e-6;
const float Y_INCPT = 0.683;

// Container Identification
// GPIO Pins; A2 = MSB; A0 = LSB
const int input_one = A2;
const int input_two = A3;
const int input_three = A4;

//Scale Instance
HX711 scale;

enum ScreenState {
    MAIN_SCREEN,
    MENU_SCREEN,
    ITEM_SCREEN
};

enum ReadingState {
    noID_message,
    noID_reading,
    posID_low_message,
    posID_low_reading,
    posID_high
};

ScreenState currentScreen = MAIN_SCREEN;
ReadingState readingState = noID_message;
int menuIndex = 0;

// Example stored data
const int itemCount = 8;

String items[itemCount] = {
    "No container",
    "Flour",
    "Almond Flour",
    "GF Flour",
    "Rye Flour",
    "Cassava Flour",
    "Cornmeal",
    "Sugar"
};

int containerWeights[itemCount] = {
    100,  // No container
    200,  // Flour
    100,  // Almond Flour
    100,  // GF Flour
    100,  // Rye Flour
    100,  // Cassava Flour
    100,  // Cornmeal
    100   // Sugar
};

// Threshold for each of the containers
int thresholds[itemCount] = {
    0,    // No container
    300,  // Flour
    500,  // Almond Flour
    500,  // GF Flour
    500, // Rye Flour
    500,  // Cassava Flour
    500,  // Cornmeal
    500  // Sugar
};

int weights[itemCount] = {
    0,     // No container
    1000,  // Flour
    900,   // Almond Flour
    1100,  // GF Flour
    1200,  // Rye Flour
    800,   // Cassava Flour
    700,   // Cornmeal
    1300   // Sugar
};

int incomingItem = 0;

int guiIndex = 0;
//Intervals
const unsigned long time_debounce = 100;
unsigned long currentTime = 0;
unsigned long lastSaveTime = 0;
const unsigned long saveInterval = 5000; // checks to save every 5 seconds
unsigned long time_Main_noID = 0;
unsigned long time_Main_posID_low = 0;

/*-----------SETUP FUNCTION-----------*/
void setup() {

    Wire.begin(22,20); // SDA, SCL for ESP32 connections

    lcd.init(); // This initializes LCD
    lcd.backlight(); // This turns on LCD backlight
    
    pinMode(tareButton, INPUT_PULLUP); // Use internal pull-up for button
    pinMode(menuButton, INPUT_PULLUP);
    pinMode(upButton, INPUT_PULLUP); 
    pinMode(tareCaptureButton, INPUT_PULLUP);
    pinMode(powerButton, INPUT_PULLUP);

    pinMode(G, OUTPUT); // This defines the pin G as output
    pinMode(Y, OUTPUT); // This defines th pin Y as output
    pinMode(R, OUTPUT); // This defines the pin R as output
    
    // Container Identification
    pinMode(input_one, INPUT);
    pinMode(input_two, INPUT);
    pinMode(input_three, INPUT);

    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); //start scale library

    Serial.begin(115200); // This initializes Serial communication

    lcd.setCursor(0,0);
    lcd.print("System Ready");

}

/*-----------SUPERLOOP-----------*/
void loop () {
    // POWER BUTTON
    // ------------
    bool powerReading = digitalRead(powerButton);

    // Detect button press (HIGH → LOW transition)
    if (lastPowerButtonState == HIGH && powerReading == LOW) {
    screenOn = !screenOn;  // toggle screen

        if (screenOn) {
            lcd.backlight();
            Serial.println("Screen ON");
        } else {
            lcd.noBacklight();
            Serial.println("Screen OFF");
            lcd.clear();
            digitalWrite(G,LOW);
            digitalWrite(Y,LOW);
            digitalWrite(R,LOW);
        }

        delay(time_debounce); // simple debounce
    }

    lastPowerButtonState = powerReading;   

    // screenOn = true;    //temp debug
    // lcd.backlight();

    if (screenOn) {
        // Container Identification
        int b0 = digitalRead(input_one);
        int b1 = digitalRead(input_two);
        int b2 = digitalRead(input_three);

        // 3-bit number output
        int incomingItem = (b2 << 2) | (b1 << 1) | b0;

        Serial.println(incomingItem);
        
        //Get current time
        unsigned long tempTime = millis();
        //Serial.println((tempTime - currentTime));
        currentTime = tempTime;

        // SCALE
        // -----
        //Read scale
        if (scale.wait_ready_timeout(100)) {
            long reading = scale.read();
            // Serial.println(reading);
            // delay(200);
            weight = (float)reading * SLOPE + Y_INCPT;  //convert value
            weight = weight * 1000;
            if (weight <= 10 && weight >= -10) {
                weight = 0;
            }                  //convert to grams
            // Serial.print("HX711 reading: ");
            // Serial.println((int)(weight*1000));
        } else {
            Serial.println("HX711 not found.");
        }
        //delay(200);
        
        // TARE BUTTON
        // -----------
        // NOTE: you have to press and hold the button for it to tare or cancel out the tare
        // Check the state of the tare button
        bool currentButtonState = digitalRead(tareButton);

        // Detect button press (HIGH → LOW transition)
        if (lastButtonState == HIGH && currentButtonState == LOW) {
            tareActive = !tareActive; // Toggle state

            if (tareActive) {
                tareOffset = weight; // store current value as tare
                Serial.print("Tare ON. New Offset = ");
                Serial.println(tareOffset);
            } else {
                tareOffset = 0;
                Serial.println("Tare OFF.");
            }

            delay(time_debounce); 
        }
        lastButtonState = currentButtonState;
        
        // Read sensor and apply tare if applicable
        int weightValue = weight - tareOffset; // subtract tare
        // Define netweight to be used for in the RED alert
        int netWeight = weightValue - containerWeights[menuIndex];

        // CONTAINER MEMORY
        // ----------------

            // SELECT ITEM BASED ON CONTAINER IDENTIFICATION NUMBER
            if (incomingItem >= 0 && incomingItem < itemCount) {
                menuIndex = incomingItem;
            }
                
            // CHECK STABILITY AND STORE MEASUREMENT
            static int lastWeight = 0;

            if (currentTime - lastSaveTime >= saveInterval) {
                lastSaveTime = currentTime;

                if (menuIndex > 0 && menuIndex < itemCount) {

                    // Check if weight hasn't changed much
                    if (abs(weightValue - lastWeight) > 5 && weightValue > 10) {
                        // STORES WEIGHT
                        int netWeight = weightValue - containerWeights[menuIndex];
                        if (netWeight > 0) {
                            weights[menuIndex] = netWeight;

                            Serial.print("Saved NET weight for ");
                            Serial.print(items[menuIndex]);
                            Serial.print(" = ");
                            Serial.println(netWeight);

                            // Clear after updating weight
                            lcd.clear();
                        }
                    }                
                }
                lastWeight = weightValue;
            }

        // ENTER/MENU BUTTON
        // -----------------
        // Note: you have to press and hold the button for it to enter the menu
        // Check the state of the enter/menu button
        bool menuReading = digitalRead(menuButton);

        // Detect press (HIGH → LOW transition)
        if (lastMenuButtonState == HIGH && menuReading == LOW) {
            
            if (currentScreen == MAIN_SCREEN) {
                currentScreen = MENU_SCREEN;
                Serial.println("Menu OPEN");
            }
            else if (currentScreen == MENU_SCREEN) {
                currentScreen = ITEM_SCREEN;
                Serial.println("Item OPEN");
            }
            else if (currentScreen == ITEM_SCREEN) {
                currentScreen = MAIN_SCREEN;
                Serial.println("Back to MAIN");
            }
            lcd.clear();
            delay(time_debounce);
        }
        lastMenuButtonState = menuReading;

        // MAIN SCREEN
        // ----------
        if (currentScreen == MAIN_SCREEN) {
            // If there is a container on top of the scale but RFID is not detected:
            // Input: Scale value is greater than 5g (Something is placed on top of the scale)
            // Output: Yellow blinking light
            // Output: Message on the LCD screen alternates with weight displayed
                // Changes that need to be made:
                // Add condition that RFID is not detected
                // See if you can make the light remain on even after the container is removed from the scale until the user taps a RFID sticker

            char weightChars[6];
            snprintf(weightChars, sizeof(weightChars), "%+05d", weightValue);
            char netWeightChars[6];
            snprintf(netWeightChars, sizeof(netWeightChars), "%+05d", netWeight);
            if (weightValue > 5 && menuIndex == 0) {
                //Serial.println("Weight Not Stored! Remember to tap the RFID Tag!");  // Prints out context information of what the code is doing
                if (currentTime - time_Main_noID < 500) {
                    if (readingState != noID_message) {
                        lcd.clear();
                        readingState = noID_message;
                    }
                    lcd.setCursor(0,0);
                    lcd.print("Tap RFID Tag!");
                    lcd.setCursor(0,1);
                    lcd.print("Weight Not Saved");
                    digitalWrite(G,LOW); // The green light is turned off
                    digitalWrite(Y,HIGH); // The yellow light is turned on
                    digitalWrite(R,LOW); // The red light is turned off
                } else if (currentTime - time_Main_noID < 2000) {
                    if (readingState != noID_reading) {
                        lcd.clear();
                        readingState = noID_reading;
                    }
                    lcd.setCursor(0,0);
                    lcd.print("Tap RFID Tag!");
                    lcd.setCursor(0,1);
                    lcd.print(weightChars); // Print the value for the scale value
                    lcd.setCursor(15,1);
                    lcd.print("g");
                    digitalWrite(G,LOW); // The green light is turned off
                    digitalWrite(Y,LOW); // The yellow light is turned off
                    digitalWrite(R,LOW);
                } else {time_Main_noID = currentTime;}

            }
            // If the ingredient is below the threshold:
            // Input: Sensor detects a weight value that is below the threshold
            // Output: Red Blinking light
            // Output: Message on the LCD screen alternates with weight displayed
            else if (menuIndex > 0 && netWeight < thresholds[menuIndex]) {
                //Serial.println("Ingredient Weight is Below Threshold!");

                if (currentTime - time_Main_posID_low < 500) {
                    if (readingState != posID_low_message) {
                        lcd.clear();
                        readingState = posID_low_message;
                    }
                    lcd.setCursor(0,0);
                    lcd.print("Weight Low!");
                    lcd.setCursor(0,1);
                    lcd.print("Refill Needed");
                    digitalWrite(G,LOW); // The green light is turned off
                    digitalWrite(Y,LOW); // The yellow light is turned off
                    digitalWrite(R,HIGH);
                } else if (currentTime - time_Main_posID_low < 2000) {
                    if (readingState != posID_low_reading) {
                        lcd.clear();
                        readingState = posID_low_reading;
                    }
                    lcd.setCursor(0,0);
                    lcd.print("NetWeight:");
                    lcd.setCursor(0,1);
                    lcd.print(netWeightChars); // Print the scale value
                    lcd.setCursor(15,1);
                    lcd.print("g"); // Print gram units to the last column in the row where the value is being printed
                    digitalWrite(G,LOW); // The green light is turned off
                    digitalWrite(Y,LOW); // The yellow light is turned off
                    digitalWrite(R,LOW); // The red light is turned off
                } else {time_Main_posID_low = currentTime;}

            }
            // Normal conditions:
            // Output: Green Light remains on
            // Output: Only weight is displayed on the LCD screen
            else {
                if (readingState != posID_high) {
                        lcd.clear();
                        readingState = posID_high;
                    }
                lcd.setCursor(0,0);
                lcd.print("Weight:");
                lcd.setCursor(0,1);
                lcd.print(weightChars); // Print scale value
                lcd.setCursor(15,1);
                lcd.print("g"); // Print gram units to the last column in the row where the value is being printed
                digitalWrite(G,HIGH); // The green light is turned on
                digitalWrite(Y,LOW); // The yellow light is turned off
                digitalWrite(R,LOW); // The red light is turned off
            }
        }

        // MENU SCREEN
        // ------------
        else if (currentScreen == MENU_SCREEN) {
            // Read button states
            bool upReading = digitalRead(upButton);

            // UP button pressed
            if (lastUpButtonState == HIGH && upReading == LOW) {
                guiIndex--;
                if (guiIndex < 0) guiIndex = itemCount - 1;

                lcd.clear();
                delay(time_debounce); 
            }

            // Save button states
            lastUpButtonState = upReading;

            // Display menu
            lcd.setCursor(0,0);
            lcd.print("Select Item:");
            lcd.setCursor(0,1);
            lcd.print(">");
            lcd.print(items[guiIndex]);
        }

        // ITEM SCREEN
        // -----------
        else if (currentScreen == ITEM_SCREEN) {

        // Read capture button
        bool captureReading = digitalRead(tareCaptureButton);

        // Only allow capture if this screen matches the identified container
        if (guiIndex == menuIndex) {

            if (lastTareCaptureButtonState == HIGH && captureReading == LOW) {

                if (menuIndex > 0 && menuIndex < itemCount && weight > 10) {

                    // Save container weight (tare-adjusted)
                    containerWeights[menuIndex] = weight - tareOffset;

                    Serial.print("Captured container weight for ");
                    Serial.print(items[menuIndex]);
                    Serial.print(" = ");
                    Serial.println(containerWeights[menuIndex]);

                    lcd.clear();
                    lcd.setCursor(0,0);
                    lcd.print("Container Saved");
                    lcd.setCursor(0,1);
                    lcd.print(items[menuIndex]);

                    delay(1000);
                    lcd.clear();
                }

                delay(time_debounce);
            }
        }

        /* if (guiIndex != menuIndex) {
        lcd.setCursor(0,1);
        lcd.print("Wrong Container");
        } */

        lastTareCaptureButtonState = captureReading;

        // Display item info
        lcd.setCursor(0,0);
        lcd.print(items[guiIndex]);

        lcd.setCursor(0,1);
        lcd.print(weights[guiIndex]);
        lcd.print(" g");
        }   
    }
}