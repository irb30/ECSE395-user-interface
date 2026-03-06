## Lab #5 (02/13/2026)

## Part 0: Check out equipment
At the start of the lab, I checked out one of the ESP32 microcontroller (#2) and the sunfounder kit (#2) and completed the ECSE 395 Equipment Check out form.

## Part 1: ESP32 + Integration Exploration
The goal of this assignment was to work on integrating sensors and actuators. This is the last assignment working with the ESP32 microcontroller. 
* Sensors used: photoresistor module and touch module
* Actuators used: LED Traffic Light Module  

The code was uploaded to the ESP32 using Visual Studio Code with PlatformIO IDE extension. This was done using Windows. The microcontroller was connected to the computrer with a USB-C cable with data transfer capabilities.     

In this respository, the code can be found inside the src folder. The code used to test the photoresistor module can be found in photoresistor.cpp. The code used to test the LED traffic light module can be found in trafficLED.cpp. The code used to test the touch sensor module can be found in touchSensor.cpp. The code used to integrated the sensors and actuator can be found in main.cpp.   

* The desired behavior of the system is as followed:
    * When the photoresistor sensor measures a value of at least 2250, it will activate the LED traffic light actuator to turn the yellow light on and off, so as to have it blinking.
        * This represents a traffic light which turns into a flashing yellow light during the night time by recognizing when the sun goes down and it is dark. 
        * To implement this effect, cover the photoresistor sensor, and the yellow light will start blinking.
    * In order to fully implement the context, I added a touch sensor. When the touch sensor measures a value of at least 1500, it will activate the LED traffic light actuator to turn the red light on for an extended amount of time.
        * This represents a traffic light which turns red when a pedestrian presses the button to cross the road.
        * To implement this effect, hold on to the touch module, and the red light will turn on.
        * Note: the pedestrian button only works during the day (when the photoresistor sensor measures a value below 1200).

1. I accepted the repository assignment named integration-exploration
2. I created a file named integration_exploration.md (this file) to document my work for lab 5.
3. I built my circuit with the ESP32, photoresistor module, touch module, LED traffic light module, breadboard, and jumper cables. The connections made were as followed:
    * Photoresistor Sensor Module:
        * The photoresistor VCC pin is connected to the 3V pin in the ESP32.
        * The photoresistor GND pin is connected to the GND pin in the ESP32.
        * The photoresistor D0 pin is not connected to anything.
        * The potoresistor A0 pin is connected to the A0 pin in the ESP32.
    * LED Traffic Light Module:
        * The traffic light GND pin is connected to the GND pin in the ESP32.
        * The traffic light R pin for the red light is connected to the D33 pin in the ESP32.
        * The traffic light Y pin for the yellow light is connected to the D27 pin in the ESP32.
        * The traffc light G pin for the green light is connected to the D12 pin in the ESP32.
    * Touch Sensor Module:
        * The touch sensor I0 pin is connected to the A1 pin in the ESP32.
        * The touch sensor VCC pin is connected to the 3V  pin in the ESP32.
        * The touch sensor GND pin is connected to the GND pin in the ESP32.

* Pictures of the circuit can be found here:
    * Front view:
    ![alt text](Photo_CircuitFront.jpg)
    * Back View:
    ![alt text](Photo_CircuitBack.jpg)
    * ESP32 Top View:
    ![alt text](Photo_CircuitESP32.jpg)
4. I added the line of code: monitor_speed = 115200 to match baud rate inside platformio.ini 
5. I uploaded the code from photoresistor.cpp to the ESP32 microcontroller and observed the behavior. This code tested out the photoresistor module and observations can be found in a subsection below.
6. I uploaded the code from trafficLED.cpp to the ESP32 microcontroller and observed the behavior. This code tested out the LED traffic light module and observations can be found in a subsection below.
7. I uploaded the code from touchSensor.cpp to the ESP32 microcontroller and observed the behavior. This code tested out the touch sensor module and observations can be found in a subsection below. 
8. I uploaded the code from main.cpp to the ESP32 microcontorller. A video of the system opperating with the custom adjustments can be found in the file Video_IntegratedSystem.MOV <video controls src="Video_IntegratedSystem.mov" title="Title"></video>

## Part 2: Check In Equipment
At the end of the lab, I checked back in the ESP32 microcontroller (#2) and the sunfounder kit (#2) and completed the ECSE 395 Equipment Check in form

## Part 3: Time Reporting and Reflection
1. How long did it take you to complete this assignment?  
It took me 4 hours to complete this assignment.
2. What level of difficulty would you associate with this assignment?  
I would associate this assignment with an easy level of difficulty.
3. If you associated medium/high difficulty with this assignment, what aspect did you find the most difficult?  
Not applicaple.
4. How comfortable do you currently feel with the course content?  
I feel comfortable integrating different sensors and activators using information I learned from previous lab assignments and information that can be found online.
5. Do you have any additional information or feedback you would like to share with the instructors?  
This lab was actually very fun. 

## Observations
### Photoresistor Observations
Afer testing the code in photoresistor.cpp, I observed the values from the sensor when the photoresistor is covered, when it is under natural room light, and when it is under a shining flashight.
* Covering the photoresistor resulted in values 2513 - 2544
* Shining light to the photoresistor resulted in values 432 - 395
* Natural room light resulted in values 987 - 1105

### LED Traffic Light Observations
The LED traffic light can be activated using analog or digital reading pin. The analog pin can change the intensity of the lights that are turned on. The digital pin will just turn the light on (when output is set to HIGH) and off (when output is set to LOW).  

For the purpose of the traffic light context, I just needed to turn the lights on and off.  

To get the blinking light effect, I used a loop that would turn on the light and then turn off the light for a 0.5 seconds each.  

To get the normal traffic light signal green to yellow to red and back to green, I used a loop again, turning on each light for a specific appropriate amount of time.

### Touch Sensor Observations
After testing the code in touchSensor.cpp, I observed that if the touch module sensor is touched, it detects a value greater than 2000. If the touch module is not engaged, it will detect a value below 1500.