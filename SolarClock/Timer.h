#ifndef TIMER_H
#define TIMER_H

#include "Arduino.h"

typedef void (*callbackFunction)(void);

class Timer
{
public:
    Timer();

    void SetTimer(int time, callbackFunction function);
  	bool CheckTimer();

  	int GetStartTime() const;

private:
    int startTime;
    int timerDuration;
    callbackFunction setMotorOff;
};


#endif