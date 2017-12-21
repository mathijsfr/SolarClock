#include "Motor.h"

#define pulseWidthDelay 5


Motor::Motor(MotorPins pins)
	: motorPins(pins)
	, steps(0)
	, motorFinished(false)
{
	pinMode(motorPins.directionPin, OUTPUT);
	pinMode(motorPins.stepPin, OUTPUT);
	pinMode(motorPins.mode1Pin, OUTPUT);
	pinMode(motorPins.sleepPin, OUTPUT);
}

Motor::~Motor()
{
}

void Motor::MotorOnForSteps(int steps)
{
	digitalWrite(motorPins.mode1Pin, LOW);
	digitalWrite(motorPins.sleepPin, HIGH);

	for (int i = 0; i < steps; ++i)
	{
		digitalWrite(motorPins.stepPin, HIGH);
	    delayMicroseconds(pulseWidthDelay);
	    digitalWrite(motorPins.stepPin, LOW);

	    delay(1);
	}

	digitalWrite(motorPins.sleepPin, LOW);
	digitalWrite(motorPins.mode1Pin, HIGH);
	this->steps = steps;
}

void Motor::SetDirection(Direction direction)
{
	if (direction == Forward)
	{
		digitalWrite(motorPins.directionPin, LOW);
	}
	else
	{
		digitalWrite(motorPins.directionPin, HIGH);
	}
}

int Motor::GetMotorPin() const
{
	return motorPins.stepPin;
}

int Motor::GetSteps() const
{
	return steps;
}

bool Motor::GetMotorFinished() const
{
	return motorFinished;
}

void Motor::SetMotorFinished(bool motorFinished)
{
	this->motorFinished = motorFinished;
}

void Motor::SetSteps(int steps)
{
	this->steps = steps;
}