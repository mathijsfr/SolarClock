#include <QueueList.h>

#include "SolarClock.h"
#include "CommunicationHandler.h"
#include "BarHandler.h"
#include "WatchDogTimer.h"
#include "Timer.h"

#include "ConfigFile.h"

#include <QueueList.h>

#define MotorCount 12
#define TimerIntervalInMillis 10

DataHandler* dataHandler;
iBarHandler* barHandler;

iCommunicationHandler* communicationHandler;
iWatchDogTimer* watchDogTimer;

Timer* timer;

SolarClock* solarClock;

QueueList <Events> eventsQueue;

bool timerTicked;

void setup()
{
	Serial.begin(9600);

	Motor* motors[MotorCount];
	for (int i = 0; i < MotorCount; ++i)
	{
		motors[i] = new Motor(motorPins[i]);
	}

	dataHandler = new DataHandler();
	barHandler = new BarHandler(motors, *dataHandler);
	communicationHandler = new CommunicationHandler(mac, server);
	watchDogTimer = new WatchDogTimer();
	timer = new Timer(TimerIntervalInMillis);

	solarClock = new SolarClock(*barHandler, *communicationHandler, *watchDogTimer);

	timerTicked = false;
	solarClock->SetUp();
}

void loop()
{
	if (eventsQueue.isEmpty())
	{
		GetEvent();
	}
	else
	{
		Events ev = eventsQueue.peek();

		solarClock->HandleEvent(ev);
		eventsQueue.pop();
	}


	checkTimer();
}	

void GetEvent()
{
	if (watchDogTimer->GetWatchDogTicked())
	{
		watchDogTimer->SetWatchDogTicked(false);
		if (watchDogTimer->GetWatchDogCounter() == 0)
		{
			eventsQueue.push(EV_WATCHDOG_DONE);
		}
		else
		{
			
			eventsQueue.push(EV_WATCHDOG_TICKED);
		}
	}

	if (communicationHandler->GetDataNotReceived())
	{
Serial.println("DataNotReceived");
		communicationHandler->SetDataNotReceived(false);
		eventsQueue.push(EV_DATA_NOT_RECEIVED);
	}
	
	if (communicationHandler->GetDataReceived())
	{
Serial.println("DataReceived");
		communicationHandler->SetDataReceived(false);
		eventsQueue.push(EV_DATA_RECEIVED);
	}
	
	if (barHandler->GetBarsReset())
	{
		barHandler->SetBarsReset(false);
		eventsQueue.push(EV_CLOCK_INITIALIZED);
	}

	if (timerTicked)
	{
		timerTicked = false;
		eventsQueue.push(EV_TIME_UP);
	}
}

void checkTimer()
{
	if(timer->IsTimePast())
	{
		timerTicked = true;
	}
}