#include "BarHandler.h"

BarHandler::BarHandler(int* motorPins, DataHandler& dataHandler)
	: barsReset(false)
	, dataHandler(dataHandler)
{
	pinMode(powerPin, OUTPUT);
  	pinMode(groundPin, OUTPUT);
  	pinMode(powerReversePin, OUTPUT);
  	pinMode(groundReversePin, OUTPUT);

	for (int i = 0; i < MotorCount; ++i)
	{
		motors[i] = new Motor(motorPins[i]);
	}
}

BarHandler::~BarHandler()
{
	for (int i = 0; i < MotorCount; ++i)
	{
		delete motors[i];
		motors[i] = NULL;
	}
}

int BarHandler::CalculateTimeCounter(int energy)
{
	//FORMULE VOOR ENERGY NAAR TIME COUNTER
}

int* BarHandler::CalculateTimeCounters(int* energies, int count)
{
	if (energies == NULL || count <= 0)
	{
		return NULL;
	}

	int counters[count];
	for (int i = 0; i < count; ++i)
	{
		counters[i] = CalculateTimeCounter(energies[i]);
	}

	return counters;
}

void BarHandler::StopPower()
{
	digitalWrite(powerPin, HIGH);
  	digitalWrite(groundPin, HIGH);
  	digitalWrite(powerReversePin, HIGH);
  	digitalWrite(groundReversePin, HIGH);
}

void BarHandler::SetDirection(Direction direction)
{
	StopPower();
	
	if (direction == Forward)
	{

	}
	else
	{

	}
}

void BarHandler::ResetBar(int motorIndex)
{
	dataHandler.RetreiveLengths(&motors[motorIndex], 1);
	SetDirection(Backward);
	motors[motorIndex]->MotorOnForTime(motors[motorIndex]->GetLength());

	motors[motorIndex]->SetMotorFinished(false);
	while(!motors[motorIndex]->GetTimer()->CheckTimer())
	{

	}
}

void BarHandler::ResetBars()
{
	dataHandler.RetreiveLengths(motors, MotorCount);
	SetDirection(Backward);

	int motorsFinished = 0;
	while(motorsFinished < MotorCount)
	{
		for (int i = 0; i < MotorCount; ++i)
		{
			if (!motors[i]->GetMotorFinished()
				&& motors[i]->GetTimer()->GetStartTime() == -1)
			{
				motors[i]->MotorOnForTime(motors[i]->GetLength());
			}
			else if (!motors[i]->GetMotorFinished()
				&& motors[i]->GetTimer()->CheckTimer())
			{
				motors[i]->SetMotorFinished(true);
				motorsFinished++;
			}
		}
	}
}

void BarHandler::SetBar(int energy, int motorIndex)
{
	int counter = CalculateTimeCounter(energy);
	SetDirection(Forward);
	motors[motorIndex]->MotorOnForTime(counter);

	while (!motors[motorIndex]->GetTimer()->CheckTimer());
}

void BarHandler::SetAllBars(int* timeCounters, int count)
{

}

bool BarHandler::GetBarsReset() const
{
	return barsReset;
}

const Motor* BarHandler::GetMotor(int motorIndex) const
{
	return motors[motorIndex];
}

void BarHandler::SetBarsReset(bool barsReset)
{
	this->barsReset = barsReset;
}