#ifndef WATCH_DOG_TIMER_H
#define WATCH_DOG_TIMER_H

#include "iWatchDogTimer.h"
#include "Arduino.h"

class WatchDogTimer : public iWatchDogTimer
{
public:
    WatchDogTimer();

    void UpdateWatchDogCounter();
    void CalculateWatchDog(LocalTime localTime);
    void EnableWatchDog();

    int GetWatchDogCounter() const;
    bool GetWatchDogTicked() const;

    void SetWatchDogTicked(bool watchDogTicked);
    void SetSleepMode(bool enableSleepMode);

private:
	#define HOUR_IN_SECONDS 3600
	#define POWERDOWNTIME_IN_SECONDS 8

    int watchDogCounter;
    bool watchDogTicked;

    void SetUp();
};


#endif