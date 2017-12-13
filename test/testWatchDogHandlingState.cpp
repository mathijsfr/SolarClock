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


TEST_F(TestWatchDogHandlingState, test_watchdog_done_event)
{
    EXPECT_EQ(State_RequestEnergy, solarClock->HandleWatchDogHandlingState(EV_WATCHDOG_DONE));
}


TEST_F(TestWatchDogHandlingState, test_watchdog_ticked_event)
{
    EXPECT_CALL(watchDogTimer, UpdateWatchDogCounter());
    EXPECT_CALL(watchDogTimer, EnableWatchDog());

    EXPECT_EQ(State_WatchDogHandling, solarClock->HandleWatchDogHandlingState(EV_WATCHDOG_TICKED));
}
