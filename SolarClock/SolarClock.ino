#include "SolarClock.h"
#include "DataHandler.h"

#define MotorCount 12

byte mac[6] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01};
String server("virtueusage.azurewebsites.net/");

int motorPins[MotorCount] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
DataHandler* dataHandler = new DataHandler();
BarHandler* barHandler = new BarHandler(motorPins, *dataHandler);

CommunicationHandler* communicationHandler = new CommunicationHandler(mac, server);
WatchDogTimer* watchDogTimer = new WatchDogTimer();

SolarClock* solarClock = new SolarClock(*barHandler, *communicationHandler, *watchDogTimer);

bool timerInteruptTicked;

void setup()
{
	Serial.begin(9600);
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