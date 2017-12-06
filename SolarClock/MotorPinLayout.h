#ifndef MOTOR_PIN_LAYOUT_H
#define MOTOR_PIN_LAYOUT_H

#define MotorCount 12

typedef struct 
{
	int directionPin;
	int stepPin;
	int mode1Pin;
} MotorPins;
								  
#endif