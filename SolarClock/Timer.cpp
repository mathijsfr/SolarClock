#include "Timer.h"

Timer::Timer(int intervalMillis)
	: interval(interval)
	, previousMillis(0)
{
	//Do nothing
}

bool Timer::TimeIsPast()
{
	if((millis() - previousMillis) >= interval)
	{
		return true;
	} 

	return false;
}