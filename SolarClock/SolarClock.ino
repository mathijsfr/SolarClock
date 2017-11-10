#include "SolarClock.h"
#include "DataHandler.h"

#define MotorCount 12

int motorPins[MotorCount] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
DataHandler dataHandler = new DataHandler();
BarHandler barhandler = new BarHandler(motorPins, &dataHandler);

CommunicationHandler communicationHandler = new CommunicationHandler();
WatchDogTimer watchDogTimer = new WatchDogTimer();

solarClock = new SolarClock(&barhandler, &communicationHandler, &watchDogTimer);

Events ev;

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	solarClock.HandleEvent(ev);
}

