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

void Timer::CheckTimer()
{
	if (startTime != -1 || timerDuration != -1 || setMotorOff != NULL)
	{
		
	}
}