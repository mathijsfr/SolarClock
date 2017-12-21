#include <avr/sleep.h>

#include "WatchDogTimer.h"
#include "LocalTime.h"

static WatchDogTimer* watchDogTimer;

WatchDogTimer::WatchDogTimer()
	: watchDogCounter(0)
	, watchDogTicked(false)
{
	watchDogTimer = this;

	cli();

	//Set Power Down mode
	MCUSR &= ~_BV(WDRF);
	SMCR |= _BV(SM1);

	//Set Powerdown 8.0s
	WDTCSR = 0x18;
	WDTCSR = 0x61;

	sei();
}

void WatchDogTimer::UpdateWatchDogCounter()
{
	watchDogCounter--;
}


void WatchDogTimer::CalculateWatchDog(LocalTime localTime)
{
	int amountOfSeconds = HOUR_IN_SECONDS - (localTime.minutes * 60 + localTime.seconds);

	watchDogCounter = 1; //amountOfSeconds / POWERDOWNTIME_IN_SECONDS;
}

void WatchDogTimer::EnableWatchDog()
{
	SetSleepMode(true);
	sleep_cpu();
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

void WatchDogTimer::SetSleepMode(bool enableSleepMode)
{
  if (enableSleepMode)
  {
    SMCR |= _BV(SE);
  }
  else
  {
    SMCR &= ~_BV(SE);
  }
}

//Interrupt
ISR(WDT_vect)
{
	watchDogTimer->SetWatchDogTicked(true);
 	watchDogTimer->SetSleepMode(false);
}