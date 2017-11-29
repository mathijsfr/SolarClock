#include "Timer.h"

Timer::Timer()
	: startTime(-1)
	, timerDuration(-1)
	, setMotorOff(NULL)
{
}

void Timer::SetTimer(int time, callbackFunction function)
{
	startTime = millis();
	timerDuration = time;
	setMotorOff = function;
}

bool Timer::CheckTimer()
{
	if (startTime != -1 || timerDuration != -1 || setMotorOff != NULL)
	{
		if (startTime + timerDuration <= millis())
		{
			setMotorOff();
			startTime = -1;
			timerDuration = -1;
			setMotorOff = NULL;
			return true;
		}
	}

	return false;
}

int Timer::GetStartTime() const
{
	return startTime;
}