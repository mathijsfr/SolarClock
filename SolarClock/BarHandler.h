#ifndef BAR_HANDLER_H
#define BAR_HANDLER_H

#include "DataHandler.h"
#include "Motor.h"
#include "Direction.h"
#include "Arduino.h"

#define powerPin 6 //INT 8
#define groundPin 2 //INT 6
#define powerReversePin 3 //INT 7
#define groundReversePin 4 //INT 5

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
    const Motor* GetMotor(int motorIndex) const;

    void SetBarsReset(bool barsReset);

private:
    void SetDirection(Direction direction);
    void StopPower();

    Motor* motors[MotorCount];
    bool barsReset;
    DataHandler& dataHandler;


};


#endif