#include "SolarClock.h"

#include "mBarHandler.h"
#include "mCommunicationHandler.h"
#include "mWatchDogTimer.h"

using ::testing::Return;
using ::testing::_;

#define MotorCount 12

class TestInitializeClockState : public ::testing::Test 
{
  protected:

    TestInitializeClockState() {
        solarClock = new SolarClock(barHandler, communicationHandler, watchDogTimer);
    }

    virtual ~TestInitializeClockState() {
        delete solarClock;
        solarClock = NULL;
    }

    mWatchDogTimer watchDogTimer;
    mBarHandler barHandler;
    mCommunicationHandler communicationHandler;
    SolarClock* solarClock;
};

TEST_F(TestInitializeClockState, test_time_up_event)
{
    EXPECT_CALL(communicationHandler, Update());
    EXPECT_EQ(State_InitializeClock, solarClock->HandleInitializeClockState(EV_TIME_UP));
}

// TEST_F(TestInitializeClockState, test_data_received_event)
// {
//     int steps[MotorCount];
//     EXPECT_CALL(communicationHandler, GetEnergies())
//                 .WillOnce(Return(int*));
//     EXPECT_CALL(barHandler, CalculateSteps(0));
//     EXPECT_CALL(ui, StopClock());
//     EXPECT_EQ(STATE_DOOR_OPENED_HEATING, microwave->HandleHeatingState(EV_DOOR_OPENED));
// }
