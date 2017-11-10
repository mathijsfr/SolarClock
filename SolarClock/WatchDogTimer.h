#ifndef WATCH_DOG_TIMER_H
#define WATCH_DOG_TIMER_H

#include "Arduino.h"

class WatchDogTimer
{
public:
    WatchDogTimer();

    void UpdateWatchDogCounter();
    void CalculateWatchDog(String localTime);
    void EnableWatchDog(bool enable);

private:
    int watchDogCounter;

};


#endif