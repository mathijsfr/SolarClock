#ifndef WATCH_DOG_TIMER_H
#define WATCH_DOG_TIMER_H

#include "iWatchDogTimer.h"

class WatchDogTimer : public iWatchDogTimer
{
public:
    WatchDogTimer();

    void UpdateWatchDogCounter();
    void CalculateWatchDog(int localTime);
    void EnableWatchDog(bool enable);

    int GetWatchDogCounter() const;
    int GetWatchDogTicked() const;

    void SetWatchDogTicked(bool watchDogTicked);

private:
    int watchDogCounter;
    bool watchDogTicked;

};


#endif