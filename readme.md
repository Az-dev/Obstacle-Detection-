<!-- heading -->
# <p align="center">Car Project</p>

* The Car project is a C application based-on Atmega32 microcontroller . The project introduces a car dirven by four wheels based on four dc motors 
* that can detect ostacles ahead and avoid it.   
____
###### __This application implements the following Features and modules -on technical behalf__-:#####
### Micro Controller Abstraction Layer (MCAL) implements the following modules ###
1. DIO   : An API for General Purpose I/O prepherials.
2. PWM   : An API for HWPWM module.    
3. Timer : An API for Timers modules.
### ECU Abstraction Layer (ECUAL) implements the following modules ###
1. Motor  : An API for dirving DC-Motors.
2. SwDelay: A module for implementing software-based time delay.
3. SwICU  : A module for implementing software-based input capture unit.
4. Us     : An API for Ultrasonic sensor.
### Application Layer (APP) ###
1. Steering : A module for implementing the wheels-steering functionality.
2. CarSm    : A module that implements system state machine of the moving and obstacle detection mechanism.
----
* ###### **Components and packages used for implementing this work** :

| Name               		|   Description                      	  											  |
| -------------------------	| ----------------------------------------------------------------------------------- |
| Atmega32-based Kit        | A kit with various prepherials. 													  |
| Four Dc motor             | Drives the four wheels          													  |
| HC-SR04 module            | Ultrasonic ranging module that provides 2cm - 400cm non-contact measurement function|
| Battery              		| A power source 				  													  |
------
>**Note** :
>The Application is in development phase which means that new enhancements and updates are being added continuously , so this is not the final form of it.

>***Disclaimer***:
I created this work for practise and learning purpose only but not for any commercial usage , so this work is not for any commercial usage.
