#include "SolarClock.h"

#define MotorCount 12

MotorPins motorPins[MotorCount] = {	{ 2, 3, 4 }, // motor 1
									{ 2, 3, 4 }, // motor 2
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
BarHandler* barHandler;

CommunicationHandler* communicationHandler;
WatchDogTimer* watchDogTimer;

SolarClock* solarClock;

bool timerInteruptTicked;

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
	communicationHandler = new CommunicationHandler();
	watchDogTimer = new WatchDogTimer();

	solarClock = new SolarClock(*barHandler, *communicationHandler, *watchDogTimer);

	timerInteruptTicked = false;
}

void loop()
{
	Events ev = GetEvent();
	solarClock->HandleEvent(ev);
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

	if (timerInteruptTicked)
	{
		timerInteruptTicked = false;
		return EV_TIME_UP;
	}

	int motorIndex = communicationHandler->GetCurrentMotor();
	if (barHandler->GetMotor(motorIndex)->GetMotorFinished())
	{
		barHandler->GetMotor(motorIndex)->SetMotorFinished(false);
		return EV_BAR_SET;
	}

	return NO_EVENT;
}

//HIER MOET NOG EEN TIMER INTERUPT