#ifndef BAR_HANDLER_H
#define BAR_HANDLER_H

#include "iBarHandler.h"
#include "Arduino.h"
#include "ConfigFile.h"

#define MotorCount 12



class BarHandler : public iBarHandler
{
public:
    BarHandler(Motor** motors, DataHandler& dataHandler);
    ~BarHandler();

    int CalculateSteps(int energy);
    void CalculateSteps(const int* energies, int* steps, int count);
    void ResetBar(int motorIndex);
    void ResetBars(int count);
    void SetBar(int energy, int motorIndex);
    void SetBars(int* energies, int count);

    bool GetBarsReset() const;
    const Motor* GetMotor(int motorIndex) const;

    void SetBarsReset(bool barsReset);

private:
    Motor* motors[MotorCount];
    bool barsReset;
    DataHandler& dataHandler;
};


#endif