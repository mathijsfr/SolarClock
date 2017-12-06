#ifndef IMOTOR_H
#define IMOTOR_H

#include "Direction.h"

class iMotor
{
public:
    virtual ~iMotor() {};

    virtual void MotorOnForSteps(int steps) = 0;
    virtual void SetDirection(Direction direction) = 0;

};

#endif
