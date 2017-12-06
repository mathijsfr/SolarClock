#include "SolarClock.h"

#include "mBarHandler.h"
#include "mCommunicationHandler.h"
#include "mWatchDogTimer.h"

using ::testing::Return;
using ::testing::_;

#define MotorCount 12

class TestRequestEnergyState : public ::testing::Test 
{
  protected:

    TestRequestEnergyState() {
        solarClock = new SolarClock(barHandler, communicationHandler, watchDogTimer);
    }

    virtual ~TestRequestEnergyState() {
        delete solarClock;
        solarClock = NULL;
    }

    mWatchDogTimer watchDogTimer;
    mBarHandler barHandler;
    mCommunicationHandler communicationHandler;
    SolarClock* solarClock;
};
