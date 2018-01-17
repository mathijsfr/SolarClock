#include <QueueList.h>

#include "SolarClock.h"
#include "CommunicationHandler.h"
#include "BarHandler.h"
#include "WatchDogTimer.h"
#include "Timer.h"

#define MotorCount 12
#define TimerIntervalInMillis 10

String server("virtueusage.azurewebsites.net");
byte mac[macLength] = { 0x90, 0xA2, 0xDA, 0x0F, 0x2E, 0x06 };
MotorPins motorPins[MotorCount] = {	{ 31, 30, 29, 28 }, // motor 1
									{ 25, 24, 23, 22 }, // motor 2
									{ 6, 2, 3, 4}, // motor 3
									{ 1, 2, 3, 4 }, // motor 4
									{ 1, 2, 3, 4 }, // motor 5
									{ 1, 2, 3, 4 }, // motor 6
									{ 1, 2, 3, 4 }, // motor 7
									{ 1, 2, 3, 4 }, // motor 8
									{ 1, 2, 3, 4 }, // motor 9
									{ 1, 2, 3, 4 }, // motor 10
									{ 1, 2, 3, 4 }, // motor 11
									{ 1, 2, 3, 4 }}; // motor 12

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