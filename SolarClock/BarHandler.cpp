#include "BarHandler.h"
#include "Direction.h"

BarHandler::BarHandler(Motor** motors, DataHandler& dataHandler)
	: barsReset(false)
	, dataHandler(dataHandler)
{
	for (int i = 0; i < MotorCount; ++i)
	{
		this->motors[i] = motors[i];
	}

	pinMode(relaysPin, OUTPUT);
}

BarHandler::~BarHandler()
{
	for (int i = 0; i < MotorCount; ++i)
	{
		delete motors[i];
		motors[i] = NULL;
	}
}

int BarHandler::CalculateSteps(int energy)
{
	//FORMULE VOOR ENERGY NAAR TIME COUNTER
	return energy;
}

void BarHandler::CalculateSteps(const int* energies, int* steps, int count)
{
	if (energies != NULL || count > 0)
	{
		for (int i = 0; i < count; ++i)
		{
			steps[i] = CalculateSteps(energies[i]);
		}
	}
}

void BarHandler::ResetBar(int motorIndex)
{
	dataHandler.RetreiveLengths(&motors[motorIndex], 1);
	motors[motorIndex]->SetDirection(Backward);
	motors[motorIndex]->MotorOnForSteps(motors[motorIndex]->GetSteps());
	
	motors[motorIndex]->SetMotorFinished(false);
}

void BarHandler::ResetBars(int count)
{
	for (int i = 0; i < count; ++i)
	{
		ResetBar(i);
	}
}

void BarHandler::SetBar(int energy, int motorIndex)
{
	motors[motorIndex]->SetDirection(Forward);
	motors[motorIndex]->MotorOnForSteps(CalculateSteps(energy));
	dataHandler.StoreLength(motors[motorIndex]);
}

void BarHandler::SetBars(int* energies, int count)
{
	for (int i = 0; i < count; ++i)
	{
		SetBar(energies[i], i);
	}
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