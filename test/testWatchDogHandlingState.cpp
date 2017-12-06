#include "SolarClock.h"

#include "mBarHandler.h"
#include "mCommunicationHandler.h"
#include "mWatchDogTimer.h"

using ::testing::Return;
using ::testing::_;

#define MotorCount 12

class TestWatchDogHandlingState : public ::testing::Test 
{
  protected:

    TestWatchDogHandlingState() {
        solarClock = new SolarClock(barHandler, communicationHandler, watchDogTimer);
    }

    virtual ~TestWatchDogHandlingState() {
        delete solarClock;
        solarClock = NULL;
    }

    mWatchDogTimer watchDogTimer;
    mBarHandler barHandler;
    mCommunicationHandler communicationHandler;
    SolarClock* solarClock;
};
