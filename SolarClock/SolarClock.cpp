
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

void SolarClock::SetUp()
{
    barHandler.ResetBars(MotorCount);
}

States SolarClock::HandleInitializeClockState(Events ev)
{
    States result = State_InitializeClock;
    Serial.println("State_InitializeClock");

    switch (ev)
    {
        case EV_CLOCK_INITIALIZED:
        {
            result = State_RequestEnergy;
            Serial.println("EV_CLOCK_INITIALIZED");
            break;
        }
        case EV_TIME_UP:
        {
            communicationHandler.Update();
            Serial.println("EV_TIME_UP");
            break;
        }
        case EV_DATA_RECEIVED:
        {
        	int steps[MotorCount];
    		barHandler.CalculateSteps(communicationHandler.GetEnergies(), steps, MotorCount);
    		barHandler.SetBars(steps, MotorCount);
        	Serial.println("EV_DATA_RECEIVED");
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
    Serial.println("State_InitializeClock");

    switch (ev)
    {
        case EV_DATA_RECEIVED:
        {
            Serial.println("EV_DATA_RECEIVED");
            communicationHandler.SetIsAllowedToRequestEnergy(false);

            int motorIndex = communicationHandler.GetCurrentMotor();
            barHandler.ResetBar(motorIndex);

            int energy = communicationHandler.GetEnergies()[motorIndex];
            int steps = barHandler.CalculateSteps(energy);

            barHandler.SetBar(motorIndex, steps);

            watchDogTimer.CalculateWatchDog(communicationHandler.GetLocalTime());

            result = State_WatchDogHandling;
            watchDogTimer.EnableWatchDog();
            break;
		}
        case EV_DATA_NOT_RECEIVED:
        {
            Serial.println("EV_DATA_NOT_RECEIVED");
            communicationHandler.SetIsAllowedToRequestEnergy(false);
            barHandler.ResetBars(MotorCount);
            result = State_InitializeClock;
            break;
        }
        case EV_TIME_UP:
        {
            Serial.println("EV_TIME_UP");
            if (communicationHandler.GetIsAllowedToRequestEnergy())
            {
            	communicationHandler.Update();
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
    Serial.println("State_WatchDogHandling");
    switch (ev)
    {
        case EV_WATCHDOG_DONE:
        {
            Serial.println("EV_WATCHDOG_DONE");
            result = State_RequestEnergy;
            break;
        }
        case EV_WATCHDOG_TICKED:
        {
            Serial.println("EV_WATCHDOG_TICKED");
            watchDogTimer.UpdateWatchDogCounter();
            watchDogTimer.EnableWatchDog();
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
