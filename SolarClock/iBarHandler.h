#ifndef I_BAR_HANDLER_H
#define I_BAR_HANDLER_H

#include "DataHandler.h"
#include "Arduino.h"

#define MotorCount 12

class iBarHandler
{
public:

    virtual int CalculateSteps(int energy) = 0;
    virtual void CalculateSteps(int* energies, int* steps, int count) = 0;
    virtual void ResetBar(int motorIndex) = 0;
    virtual void ResetBars() = 0;
    virtual void SetBar(int energy, int motorIndex) = 0;
    virtual void SetAllBars(int* energies, int count) = 0;

    virtual bool GetBarsReset() const = 0;
    virtual const Motor* GetMotor(int motorIndex) const = 0;

    virtual void SetBarsReset(bool barsReset);
};


#endif