#include "WatchDogTimer.h"

WatchDogTimer::WatchDogTimer()
	: watchDogCounter(0)
	, watchDogTicked(false)
{
}

void WatchDogTimer::UpdateWatchDogCounter()
{
	watchDogCounter--;
}


void WatchDogTimer::CalculateWatchDog(int localTime)
{
	//TODO this function
	localTime++;
}

void WatchDogTimer::EnableWatchDog(bool enable)
{
	//TODO this function
	if (enable)
	{
		
	}
}

int WatchDogTimer::GetWatchDogCounter() const
{
	return watchDogCounter;
}

int WatchDogTimer::GetWatchDogTicked() const
{
	return watchDogTicked;
}

void WatchDogTimer::SetWatchDogTicked(bool watchDogTicked)
{
	this->watchDogTicked = watchDogTicked;
}
