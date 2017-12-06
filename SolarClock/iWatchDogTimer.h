#ifndef I_WATCH_DOG_TIMER_H
#define I_WATCH_DOG_TIMER_H

class iWatchDogTimer
{
public:
    virtual void UpdateWatchDogCounter() = 0;
    virtual void CalculateWatchDog(int localTime) = 0;
    virtual void EnableWatchDog(bool enable) = 0;

    virtual int GetWatchDogCounter() const = 0;
    virtual int GetWatchDogTicked() const = 0;

    virtual void SetWatchDogTicked(bool watchDogTicked) = 0;

};


#endif