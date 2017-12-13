#ifndef LOCAL_TIME_H
#define LOCAL_TIME_H

#include "Arduino.h"

typedef struct 
{
	byte hours;
	byte minutes;
	byte seconds;
} LocalTime;

#endif