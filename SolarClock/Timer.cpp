#include "Timer.h"

Timer::Timer(int intervalMillis)
	: interval(interval)
	, previousMillis(millis())
{
	//Do nothing
}

bool Timer::TimeIsPast()
{
	if((millis() - previousMillis) >= interval)
	{
		previousMillis = millis();
		return true;
	} 

	return false;
}