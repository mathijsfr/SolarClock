#ifndef MOTOR_H
#define MOTOR_H

#include "IMotor.h"
#include "Timer.h"

#include "Arduino.h"

class Motor : public iMotor
{
public:
    Motor(int pin);
    ~Motor();
    
  	void On();
    void MotorOnForTime(int time);

    int GetMotorPin() const;
  	int GetLength() const;
  	bool GetMotorFinished() const;
  	const Timer* GetTimer() const;

    void SetMotorFinished(bool motorFinished);
    void SetLength(int length);

private:
    int motorPin;
    int length;
    bool motorFinished;
    Timer* timer;

};


#endif