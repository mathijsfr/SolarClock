#include "SolarClock.h"
#include "CommunicationHandler.h"
#include "BarHandler.h"
#include "WatchDogTimer.h"
#include "Timer.h"

#define MotorCount 12
#define TimerIntervalInMillis 10

String server("virtueusage.azurewebsites.net");
byte mac[6] = {0x90, 0xA2, 0xDA, 0x0D, 0x1A, 0x6A};
MotorPins motorPins[MotorCount] = {	{ 30, 29, 28 }, // motor 1
									{ 24, 23, 22 }, // motor 2
									{ 2, 3, 4 }, // motor 3
									{ 2, 3, 4 }, // motor 4
									{ 2, 3, 4 }, // motor 5
									{ 2, 3, 4 }, // motor 6
									{ 2, 3, 4 }, // motor 7
									{ 2, 3, 4 }, // motor 8
									{ 2, 3, 4 }, // motor 9
									{ 2, 3, 4 }, // motor 10
									{ 2, 3, 4 }, // motor 11
									{ 2, 3, 4 }}; // motor 12

DataHandler* dataHandler;
iBarHandler* barHandler;

iCommunicationHandler* communicationHandler;
iWatchDogTimer* watchDogTimer;

Timer* timer;

SolarClock* solarClock;

bool timerInterruptTicked;

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

	timerInterruptTicked = false;
}

void loop()
{

}	

Events GetEvent()
{
	if (watchDogTimer->GetWatchDogTicked())
	{
		watchDogTimer->SetWatchDogTicked(false);
		return EV_WATCHDOG_TICKED;
	}

	if (communicationHandler->GetDataNotReceived())
	{
		communicationHandler->SetDataNotReceived(false);
		return EV_DATA_NOT_RECEIVED;
	}
	
	if (communicationHandler->GetDataReceived())
	{
		communicationHandler->SetDataReceived(false);
		return EV_DATA_RECEIVED;
	}
	
	if (barHandler->GetBarsReset())
	{
		barHandler->SetBarsReset(false);
		return EV_CLOCK_INITIALIZED;
	}

	if (watchDogTimer->GetWatchDogCounter() <= 0)
	{
		return EV_WATCHDOG_DONE;
	}

	if (timerInterruptTicked)
	{
		timerInterruptTicked = false;
		return EV_TIME_UP;
	}

	return NO_EVENT;
}

void checkTimerInterupt()
{
	if(timer->TimeIsPast())
	{
		timerInterruptTicked = true;
	}
}