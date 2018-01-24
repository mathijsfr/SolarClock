## Solar Clock

This repository contains the code for the clock that will show the energy usage of the entire day at an interval of 1 hour. The code is made to be used with stepper motor and certain stepper motor drivers. More on this can be found on google drive.

### note

The config and the .ino file that can be found in this repository contains all the variables that need to be changed when creating the clock. This contains:

- **server**, the adress of the website that the data is stored on.
- **mac**, mac is the mac adress for the communication. This depends on the ethernet shield that is used.
- **motorPins** array, this array contains structs of the motor pins of every motor. This needs to be changed according to your wiring.
- **MULTIPLIER**, this is the amount 
- **GEAR_RADIUS**, the radius of the gear that will be used on the gear rack with the motor to extend and retract the bars on the clock.
- **STEPS_BAR_VISUAL**, the amount of steps that the bar needs to extend to be visual behind the edge of the clock.


The documents about this project can be found on google drive in Solar Clock -> Documentatie -> Master Documents.

Follow this tutorial to setup the arduino IDE for sublime:
https://github.com/Robot-Will/Stino 
