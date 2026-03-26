# MVP (03/25/2026)

### Short Written Description
#### What did you build? Briefly describe your MVP and how it works.
For our functional MVP, our team created a very usable kitchen scale system which is used to track ingredient weights and identify specific containers. Our device is a higher fidelity and scaled up version than our prototype 3 because this MVP has a front panel with an I2C display, 2 external protoboards that control user input and container identification, and a connection to the user interface through a breadboard. The user interface breadboard has a menu screen and several buttons to control differing weights and differing ingredients to display that on the screen, which is on the scale. The user interface protoboard has 5 buttons and 3 LEDs that allow user interaction with the system and interacts with the screen, while the container identification board has 3 GPIO inputs that allows for 8 unique options for ingredients, with 3 LEDs and 3 resistors. These inputs are physically selected through the sticky notes (for simulation) and solder bus wire, and the device then encodes them and figures out the active ingredient, similar to an RFID tag. Hence, when a container is placed on the scale, the device reads its weight, identifies the specific container’s ingredients, and displays and updates the information on the screen. Therefore, our overall system integrates hardware and firmware to create a functional device that hopefully fixes our stakeholder’s problem of knowing the weight of every ingredient.

#### What feedback did you incorporate? Summarize the most important feedback you received from your midterm design review and explain how it influenced your current design.
We received a lot of feedback from our peers on our midterm presentation, which helped us incorporate new things and make our MVP as well as our validation plan better. One of the main pieces of criticism we got was to connect our specifications to more clear, measurable validation metrics. For example, one of our TS was to achieve over 90% first-time user success, but this is very difficult to truly measure, as pointed out by other people. So, we changed our metrics by making our validation plan more clear in order to measure our user’s success in more clear ways, such as task completion time, error rate, and success rate on the first attempt. In addition, other feedback we received was about the realisticness of some of our TS, such as the 1.5 year battery life specification, which in hindsight, might be a lot. We also got feedback on our system complexity and container identification usage too. So, using this feedback, we decided to really focus on these parts, such as building a protoboard using GPIO encoding to simulate RFID functions, in order to really test this subsystem and its critical parts to our overall MVP. Specifically, we also tested edge cases, such as what happens when no container is selected to make sure we really incorporate the feedback and test everything out. Hence, the feedback we received was very helpful and helped us improve our MVP and validation protocol.

#### What core functionality does your MVP demonstrate? What key requirement or assumption does this prototype allow you to test?
Our MVP essentially tests the core functionality of integrating the weight measurement system with the user interface and the container identification parts in order to track different ingredient weights easily. Specifically, it clearly tests the assumption that a user can quickly select a container with an ingredient in it, while also accurately getting its weight as well in real time. The three parts of our scale, container identification, and user interface all help test this in parallel. Our MVP also demonstrates that the system processes inputs, displays outputs, updates those outputs, and functions through our improved firmware design, such as having non-blocking delays. Overall, our MVP tests the accuracy and usability of combining multiple subsystems from our original prototypes, which are input handling, identification, and measurement, into a clean user experience.

#### What are the biggest remaining risks or unknowns? What are you still unsure about?
In terms of remaining risks and uncertainties, there are still a couple that we should worry about. Even though our MVP is clear and works in a controlled manner in Glennan, we would want to see if our device can handle a messy kitchen environment that includes flour or water accidentally spilled. There is a risk that our device stops working when something spills on it, so that is definitely a risk given baking is messy. There are also risks associated with having multiple containers, interference, or potential misreads because we don’t want to confuse the user. One thing we are still unsure about is the usability of whether first-time users will understand how to use our device without any guidance, but this will be tested during our validation. There are also uncertainties on our power consumption because we want a long battery life, but we have a lot of components on our MVP, such as LEDs, buttons, sensors, and several resistors on multiple protoboards, so this is a concern too.

#### What will you test next week? Describe your validation plan at a high level.
After finishing our MVP, next week, we plan to begin our validation testing on our MVP, in which we plan to conduct a clear, easy validation study that will demonstrate how usable, realistic, and effective our device is. We plan to test several things during validation, but overall, it will test the accuracy and usability of our device for a user. In a controlled kitchen environment, we will have a user, who is a hobbyist baker/college student (and if we have time, another college student with no baking experience), to complete simple baking tasks using a standard scale and our device without prior instruction, allowing us to measure first-time success rate, task completion time, and error rates to check our >90% usability goal easily. We will also test our device reliability by tracking the amount of successful container identifications, weight recordings, and the frequency of when users forget to update the containers, which was important to our stakeholder. Since most of our protoboards have LEDs on them to alert the user clearly, we hope this can help users. We will specifically design tasks so that the ingredient weights fall below 500g when following the recipe, so we can test if users pay attention to the LED alerts and act on them. Last, we will also collect data on our users’ current ingredient tracking habits to compare them with our own system in order to check if our device prevents last-minute shortages, which was the intended goal. Thus, our validation plan incorporates the feedback that we got and tests the quantitative, technical, and qualitative user aspects of our device to determine if our MVP has an impact on bakers.


### Team Progress and Responsibilities
What each team member contributed since the midterm
We all worked together and split the work equally for the midterm presentation. After that, in order to complete our MVP, we divided most of the work equally again to finish for this assignment. Below is a breakdown of what each person did since the midterm:

#### Ben Roy:
Designed CAD and 3D printed the bigger and more complete version of our prototype 3 scale
Edited the overall firmware to make it work; specifically, switched to non-blocking delays, and edited container ID firmware
Made the MVP breadboard, calibrated the whole system
Completed overall construction of our total MVP and overall firmware to make sure everything works
Helped with photos/videos/demo
Did a lot of work for this assignment

#### Isadora Barbosa:
Added buttons to our Prototype 2’s version to make it more functionally complete for our MVP
Wrote a majority of the firmware/code on VSCode to make sure it works with differing weights are displayed on the menu screen as well as buttons and LEDs to show it working
Fixed the scale alerts, fixed the container memory firmware to make sure the system can remember the container from before, and did the overall wiring diagram
Completed overall construction of our total MVP and overall firmware to make sure everything works
Helped with photos/videos/demo
Did a lot of work for this assignment

#### Sai Subramanian:
Designed, created, and soldered a protoboard for the container identification/RFID aspect of our MVP that attaches to the scale and where LEDs light up when a specific container is selected
Did bring-up on the protoboard to make sure it works as intended
Did container identification firmware for the board as well to make sure it outputs a value from 0 to 7 given 3 GPIO inputs for a selected ingredient 
Made container tags with sticky notes and solder bus wire for the overall complete system to simulate choosing ingredients for our demo
Helped with photos/videos/demo
Helped with most parts and stayed till the end to help with overall construction of MVP

#### Amare Brown:
Designed, created, and soldered a protoboard for the user interface that can be attached to the scale with 5 buttons and 3 LEDs
Did bring-up on the protoboard to make sure it works with our complete system
Helped with photos/videos/demo and stayed till the end on Wednesday


### What each team member will do before validation testing
We will all work together to divide the work evenly for our validation testing assignment as well, making sure we can test our MVP well. We aim to have a good plan setup before the actual testing.

#### Ben Roy (works with Sai):
Invite/call 1 person to test our MVP and arrange a possible date for it
Make our MVP better (fix any mistakes)
Help create a clear, synthesized, followable validation testing protocol from that assignment
Log the stats after user completes using our device after testing

#### Isadora Barbosa (works with Amare):
Invite/call 1 person to test our MVP and arrange a possible date for it
Will log user’s data and work they use our MVP
Log the stats after user completes using our device after testing

#### Sai Subramanian (works with Ben):
Invite/call 1 person to test our MVP and arrange a possible date for it
Make our MVP better (fix any mistakes)
Help create a clear, synthesized, followable validation testing protocol from that assignment
Log the stats after user completes using our device after testing

#### Amare Brown (works with Isadora):
Invite/call 1 person to test our MVP and arrange a possible date for it
Will log user’s data and work when they use our MVP
Log the stats after user completes using our device after testing
