#ifndef BAR_HANDLER_H
#define BAR_HANDLER_H

#include "DataHandler.h"
#include "Motor.h"
#include "Arduino.h"

#define MotorCount 12

class BarHandler
{
public:
    BarHandler(int* motorPins, DataHandler& dataHandler);
    ~BarHandler();

    int CalculateTimeCounter(int energy);
    int* CalculateTimeCounters(int* energies, int count);
    void ResetBar(int motorIndex);
    void ResetBars();
    void SetBar(int energy, int motorIndex);
    void SetAllBars(int* timeCounters, int count);

    bool GetBarsReset() const;

private:
    Motor* motors[MotorCount];
    bool barsReset;
    DataHandler& dataHandler;


};


#endif