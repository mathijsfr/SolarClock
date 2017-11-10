#include "BarHandler.h"

BarHandler::BarHandler(int* motorPins, DataHandler& dataHandler)
	: barsReset(false)
	, dataHandler(dataHandler)
{
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

}

int* BarHandler::CalculateTimeCounters(int* energies, int count)
{

}

void BarHandler::ResetBar(int motorIndex)
{

}

void BarHandler::ResetBars()
{

}

void BarHandler::SetBar(int energy, int motorIndex)
{

}

void BarHandler::SetAllBars(int* timeCounters, int count)
{

}

bool BarHandler::GetBarsReset() const
{
	
}