
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
Serial.print("State_InitializeClock : ");
Serial.println(ev);

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
Serial.print("State_RequestEnergy : ");
Serial.println(ev);

    States result = State_RequestEnergy;

    switch (ev)
    {
        case EV_DATA_RECEIVED:
        {
Serial.println("SetIsAllowedToRequestEnergy=False");
            communicationHandler.SetIsAllowedToRequestEnergy(false);

Serial.print("ResetBar, motor: ");
            int motorIndex = communicationHandler.GetCurrentMotor();

Serial.println(motorIndex);
            barHandler.ResetBar(motorIndex);

Serial.println("GetEnergies");
            int energy = communicationHandler.GetEnergies()[motorIndex];
            int steps = barHandler.CalculateSteps(energy);

Serial.println("SetBar");
            barHandler.SetBar(motorIndex, steps);

Serial.println("CalculateWatchdog");
            watchDogTimer.CalculateWatchDog(communicationHandler.GetLocalTime());

Serial.println("Result=State_WatchDogHandling");
            result = State_WatchDogHandling;
            watchDogTimer.EnableWatchDog();
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
Serial.print("State_WatchDogHandling : ");
Serial.println(ev);

    States result = State_WatchDogHandling;
    switch (ev)
    {
        case EV_WATCHDOG_DONE:
        {
            result = State_RequestEnergy;
            break;
        }
        case EV_WATCHDOG_TICKED:
        {
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
