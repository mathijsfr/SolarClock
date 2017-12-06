
#include "SolarClock.h"
#include "Arduino.h"

#define MotorCount 12

SolarClock::SolarClock(iBarHandler& barHandler, iCommunicationHandler& communicationHandler, iWatchDogTimer& watchDogTimer)
	: currentState(State_InitializeClock)
    , barHandler(barHandler)
    , communicationHandler(communicationHandler)
    , watchDogTimer(watchDogTimer)
{
}

States SolarClock::HandleInitializeClockState(Events ev)
{
    States result = State_InitializeClock;

    switch (ev)
    {
        case EV_CLOCK_INITIALIZED:
        {
            result = State_RequestEnergy;
            break;
        }
        case EV_TIME_UP:
        {
            communicationHandler.Update();
            break;
        }
        case EV_DATA_RECEIVED:
        {
        	int steps[MotorCount];
    		barHandler.CalculateSteps(communicationHandler.GetEnergies(), steps, MotorCount);
    		barHandler.SetBars(steps, MotorCount);
        	
        	break;
       	}
        default:
            // ignored event, nothing to do here
            break;
    }

    return result;
}

States SolarClock::HandleRequestEnergyState(Events ev)
{
    States result = State_RequestEnergy;

    switch (ev)
    {
        case EV_DATA_RECEIVED:
        {
            communicationHandler.SetIsAllowedToRequestEnergy(false);

            int motorIndex = communicationHandler.GetCurrentMotor();
            barHandler.ResetBar(motorIndex);

            int energy = communicationHandler.GetEnergies()[motorIndex];
            int steps = barHandler.CalculateSteps(energy);

            barHandler.SetBar(motorIndex, steps);
            result = State_WatchDogHandling;
            break;
		}
        case EV_DATA_NOT_RECEIVED:
        {
            communicationHandler.SetIsAllowedToRequestEnergy(false);
            barHandler.ResetBars(MotorCount);
            result = State_InitializeClock;
            break;
        }
        case EV_TIME_UP:
        {
            if (communicationHandler.GetIsAllowedToRequestEnergy())
            {
            	communicationHandler.Update();
            }
            else
            {
            	communicationHandler.RequestIsAllowed();
            }
            break;
        }
        default:
            // ignored event, nothing to do here
            break;
    }

    return result;
}

States SolarClock::HandleWatchDogHandlingState(Events ev)
{
    States result = State_WatchDogHandling;

    switch (ev)
    {
        case EV_WATCHDOG_DONE:
        {
            watchDogTimer.EnableWatchDog(false);
            result = State_RequestEnergy;
            break;
        }
        case EV_WATCHDOG_TICKED:
        {
            watchDogTimer.UpdateWatchDogCounter();
            watchDogTimer.EnableWatchDog(true);
            break;
        }
        default:
            // ignored event, nothing to do here
            break;
    }

    return result;
}

void SolarClock::HandleEvent(Events ev)
{
    switch (currentState)
    {
        case State_InitializeClock:
            currentState = HandleInitializeClockState(ev);
            break;
            
        case State_RequestEnergy:
            currentState = HandleRequestEnergyState(ev);
            break;

        case State_WatchDogHandling:
            currentState = HandleWatchDogHandlingState(ev);
            break;

        default:
            //Serial.print("ERROR: illegal/unhandled state with number: ");
            //Serial.println(currentState);
            break;
    };
}
