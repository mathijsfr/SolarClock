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

    int GetWatchDogCounter() const;
    int GetWatchDogTicked() const;

    void SetWatchDogTicked(bool watchDogTicked);

private:
    int watchDogCounter;
    bool watchDogTicked;

};


#endif