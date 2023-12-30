# Speed Control on an Electric Car

This project was developed for a PICMICRO 18F4550, utilizing PICCompiler and Proteus for simulation.

The project was undertaken as part of a university course titled "Sistemas Electrónicos Digitales" (Digital Electronic Systems). The primary objective of this project was to create a speed control system for driving an electric car on highways or high-speed roads. Two ultrasonic sensors are employed, one positioned at the front and the other at the rear of the car. These sensors emit ultrasonic signals and calculate the distance to an object by measuring the delay of the signal.

If an object is detected approaching from the rear, the microcontroller will increase the speed of the electric motor. Conversely, if there is a potential obstacle in front of the vehicle, the controller will reduce the speed. If neither of these scenarios is detected, the speed will continue to increase until it reaches approximately 180 revolutions per minute (rpm).

Additionally, the system incorporates controls for lights and a buzzer that functions as an alarm to attract the driver's attention.
