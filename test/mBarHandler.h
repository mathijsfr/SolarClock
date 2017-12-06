#ifndef M_BAR_HANDLER_H
#define M_BAR_HANDLER_H

#include <gmock/gmock.h>
#include "iBarHandler.h"

class mBarHandler : public iBarHandler
{
    public:
        MOCK_METHOD1(CalculateSteps, int(int energy));
        MOCK_METHOD3(CalculateSteps, void(int* energies, int* steps, int count));
        MOCK_METHOD1(ResetBar, void(int motorIndex));
        MOCK_METHOD0(ResetBars, void());
        MOCK_METHOD2(SetBar, void(int energy, int motorIndex));
        MOCK_METHOD2(SetAllBars, void(int* energies, int count));
        
        MOCK_CONST_METHOD0(SetAllBars, bool());
        MOCK_CONST_METHOD1(GetMotor, Motor*(int motorIndex));
        
        MOCK_METHOD1(SetBarsReset, void(bool barsReset));
};

#endif
