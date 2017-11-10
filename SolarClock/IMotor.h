#ifndef IMOTOR_H
#define IMOTOR_H

class iMotor
{
public:
    virtual ~iMotor() {};

    virtual void On() = 0;
    virtual void Off() = 0;
};

#endif
