#include "Motor.h"

static Motor* myMotor;

Motor::Motor(int pin)
	: motorPin(pin)
	, length(0)
	, motorFinished(false)
{
	timer = new Timer();
	myMotor = this;
}

Motor::~Motor()
{
	delete timer;
	timer = NULL;
}

void Off() {
    int pin = myMotor->GetMotorPin();
    digitalWrite(pin, HIGH);
}

void Motor::On()
{
	digitalWrite(motorPin, LOW);
}

void Motor::MotorOnForTime(int time)
{
	On();
	timer->SetTimer(time, Off);
}

int Motor::GetMotorPin() const
{
	return motorPin;
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

void Motor::SetMotorFinished(bool motorFinished)
{
	this->motorFinished = motorFinished;
}

void Motor::SetLength(int length)
{
	this->length = length;
}