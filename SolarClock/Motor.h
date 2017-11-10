#ifndef MOTOR_H
#define MOTOR_H

#include "IMotor.h"
#include "Timer.h"

class Motor : public iMotor
{
public:
    Motor(int pin);
    ~Motor();
    
  	void On();
  	void Off();

  	int GetLength() const;
  	bool GetMotorFinished() const;
  	const Timer* GetTimer() const;

private:
    int motorPin;
    int length;
    bool motorFinished;
    Timer* timer;

};


#endif