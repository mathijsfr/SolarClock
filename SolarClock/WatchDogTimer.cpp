#include "WatchDogTimer.h"

WatchDogTimer::WatchDogTimer()
	: watchDogCounter(0)
	, watchDogTicked(false)
{

}

void WatchDogTimer::UpdateWatchDogCounter()
{

}


void WatchDogTimer::CalculateWatchDog(String localTime)
{

}

void WatchDogTimer::EnableWatchDog(bool enable)
{
	
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
