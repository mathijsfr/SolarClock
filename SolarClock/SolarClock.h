#ifndef SOLAR_CLOCK_H
#define SOLAR_CLOCK_H

#include "Events.h"
#include "States.h"
#include "iBarHandler.h"
#include "iCommunicationHandler.h"
#include "iWatchDogTimer.h"

#include "Arduino.h"

class SolarClock
{
public:
    SolarClock(iBarHandler& barHandler, iCommunicationHandler& communicationHandler, iWatchDogTimer& watchDogTimer);

    void SetUp();

    void HandleEvent(Events ev);
    States HandleInitializeClockState(Events ev);
    States HandleRequestEnergyState(Events ev);
    States HandleDisplayEnergyState(Events ev);
    States HandleRequestTimeState(Events ev);
    States HandleWatchDogHandlingState(Events ev);

private:
    States currentState;
    iBarHandler& barHandler;
    iCommunicationHandler& communicationHandler;
    iWatchDogTimer& watchDogTimer;

};

#endif
