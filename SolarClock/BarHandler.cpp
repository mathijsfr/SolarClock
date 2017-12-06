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
}

void BarHandler::CalculateSteps(int* energies, int* steps, int count)
{
	if (energies == NULL || count <= 0)
	{
		return NULL;
	}

	for (int i = 0; i < count; ++i)
	{
		steps[i] = CalculateSteps(energies[i]);
	}
}

void BarHandler::ResetBar(int motorIndex)
{
	dataHandler.RetreiveLengths(&motors[motorIndex], 1);
	motors[motorIndex]->SetDirection(Backward);
	motors[motorIndex]->MotorOnForSteps(motors[motorIndex]->GetSteps());

	motors[motorIndex]->SetMotorFinished(false);
}

void BarHandler::ResetBars()
{
	// dataHandler.RetreiveLengths(motors, MotorCount);
	// SetDirection(Backward);

	// int motorsFinished = 0;
	// while(motorsFinished < MotorCount)
	// {
	// 	for (int i = 0; i < MotorCount; ++i)
	// 	{
	// 		if (!motors[i]->GetMotorFinished()
	// 			&& motors[i]->GetTimer()->GetStartTime() == -1)
	// 		{
	// 			motors[i]->MotorOnForTime(motors[i]->GetSteps());
	// 		}
	// 		else if (!motors[i]->GetMotorFinished()
	// 			&& motors[i]->GetTimer()->CheckTimer())
	// 		{
	// 			motors[i]->SetMotorFinished(true);
	// 			motorsFinished++;
	// 		}
	// 	}
	// }
}

void BarHandler::SetBar(int energy, int motorIndex)
{
	int steps = CalculateSteps(energy);
	motors[motorIndex]->SetDirection(Forward);
	motors[motorIndex]->MotorOnForSteps(steps);
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