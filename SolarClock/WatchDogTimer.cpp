#include <avr/sleep.h>

#include "WatchDogTimer.h"
#include "LocalTime.h"

static WatchDogTimer* watchDogTimer;

WatchDogTimer::WatchDogTimer()
	: watchDogCounter(0)
	, watchDogTicked(false)
{
	watchDogTimer = this;
	SetUp();
	SetSleepMode(false);
}

void WatchDogTimer::SetUp()
{
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
Serial.println("calculate");
	watchDogCounter--;
}


void WatchDogTimer::CalculateWatchDog(LocalTime localTime)
{
Serial.println("calculate");
	int amountOfSeconds = HOUR_IN_SECONDS - (localTime.minutes * 60 + localTime.seconds);

	watchDogCounter = 1; //amountOfSeconds / POWERDOWNTIME_IN_SECONDS;
}

void WatchDogTimer::EnableWatchDog()
{
Serial.println("enable");
	SetSleepMode(true);
	sleep_cpu();
}

int WatchDogTimer::GetWatchDogCounter() const
{
	return watchDogCounter;
}

bool WatchDogTimer::GetWatchDogTicked() const
{
	return watchDogTicked;
}

void WatchDogTimer::SetWatchDogTicked(bool watchDogTicked)
{
Serial.print("set ticked ");
Serial.println(watchDogTicked);
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