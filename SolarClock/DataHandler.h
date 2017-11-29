#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include "Motor.h"
#include "Arduino.h"
#include "EEPROM.h"

class DataHandler
{
public:
    DataHandler() { };

    void StoreLength(Motor* motor);
    void RetreiveLengths(Motor** motors, int count);

private:

};


#endif