#ifndef SOLAR_CLOCK_H
#define SOLAR_CLOCK_H

#include "Events.h"
#include "States.h"
#include "BarHandler.h"
#include "CommunicationHandler.h"
#include "WatchDogTimer.h"

class SolarClock
{
public:
    SolarClock(BarHandler& barHandler, CommunicationHandler& communicationHandler, WatchDogTimer& watchDogTimer);

    void HandleEvent(Events ev);
    States HandleInitializeClockState(Events ev);
    States HandleRequestEnergyState(Events ev);
    States HandleDisplayEnergyState(Events ev);
    States HandleRequestTimeState(Events ev);
    States HandleWatchDogHandlingState(Events ev);

private:
    States currentState;
    BarHandler& barHandler;
    CommunicationHandler& communicationHandler;
    WatchDogTimer& watchDogTimer;

};

#endif
