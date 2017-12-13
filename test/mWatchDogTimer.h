#ifndef M_WATCH_DOG_TIMER_H
#define M_WATCH_DOG_TIMER_H

#include <gmock/gmock.h>
#include "iWatchDogTimer.h"

class mWatchDogTimer : public iWatchDogTimer
{
    public:
        MOCK_METHOD0(UpdateWatchDogCounter, void());
        MOCK_METHOD1(CalculateWatchDog, void(int localTime));
        MOCK_METHOD0(EnableWatchDog, void());

        MOCK_CONST_METHOD0(GetWatchDogCounter, int());
        MOCK_CONST_METHOD0(GetWatchDogTicked, int());

        MOCK_METHOD1(SetWatchDogTicked, void(bool watchDogTicked));
};

#endif
