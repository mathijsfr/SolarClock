#ifndef TIMER_H
#define TIMER_H

#include "Arduino.h"

class Timer
{
public:
	Timer(int intervalMillis);
	bool TimeIsPast();

private:
	int interval;
	long previousMillis;

};

#endif