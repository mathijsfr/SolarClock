#ifndef TIMER_H
#define TIMER_H

typedef void (*callbackFunction)(void);

class Timer
{
public:
    Timer();

    void SetTimer(int time, callbackFunction function);
  	void CheckTimer();

private:
    int startTime;
    int timerDuration;
    callbackFunction setMotorOff;
};


#endif