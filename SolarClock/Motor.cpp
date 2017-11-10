#include "Motor.h"

Motor::Motor(int pin)
	: motorPin(pin)
	, length(0)
	, motorFinished(false)
{
	timer = new Timer();
}

Motor::~Motor()
{
	delete timer;
	timer = NULL;
}

void Motor::On()
{

}

void Motor::Off()
{

}

int Motor::GetLength() const
{
	return length;
}

bool Motor::GetMotorFinished() const
{
	return motorFinished;
}

const Timer* Motor::GetTimer() const
{
	return timer;
}