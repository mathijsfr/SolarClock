#ifndef I_WATCH_DOG_TIMER_H
#define I_WATCH_DOG_TIMER_H

#include "LocalTime.h"

class iWatchDogTimer
{
public:
    virtual void UpdateWatchDogCounter() = 0;
    virtual void CalculateWatchDog(LocalTime localTime) = 0;
    virtual void EnableWatchDog() = 0;

    virtual int GetWatchDogCounter() const = 0;
    virtual int GetWatchDogTicked() const = 0;

    virtual void SetWatchDogTicked(bool watchDogTicked) = 0;
    virtual void SetSleepMode(bool enableSleepMode) = 0;

};


#endif