#include "Timer.h"

Timer::Timer(int intervalMillis)
	: interval(interval)
	, previousMillis(millis())
{
	//Do nothing
}

bool Timer::IsTimePast()
{
	if((millis() - previousMillis) >= interval)
	{
		previousMillis = millis();
		return true;
	} 

	return false;
}