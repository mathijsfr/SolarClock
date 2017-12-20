#ifndef MOTOR_H
#define MOTOR_H

#include "IMotor.h"
#include "MotorPinLayout.h"

#include "Arduino.h"

#define relaysPin 50

class Motor : public iMotor
{
public:
    Motor(MotorPins motorPins);
    ~Motor();
    
    void MotorOnForSteps(int steps);

    int GetMotorPin() const;
  	int GetSteps() const;
  	bool GetMotorFinished() const;

    void SetDirection(Direction direction);
    void SetMotorFinished(bool motorFinished);
    void SetSteps(int steps);

private:
    MotorPins motorPins;
    int steps;
    bool motorFinished;

};


#endif