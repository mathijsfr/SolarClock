#include "SolarClock.h"

#include "mBarHandler.h"
#include "mCommunicationHandler.h"
#include "mWatchDogTimer.h"

using ::testing::Return;
using ::testing::_;

class TestHandleInitializeClockState : public ::testing::Test {
  protected:

    TestHandleInitializeClockState() {
        solarClock = new SolarClock(barHandler, communicationHandler, watchDogTimer);
    }

    virtual ~TestHandleInitializeClockState() {
        delete solarClock;
        solarClock = NULL;
    }

    mBarHandler barHandler;
    mCommunicationHandler communicationHandler;
    mWatchDogTimer watchDogTimer;
    SolarClock* solarClock;
};

// TEST_F(TestHeatingState, test_power_changed_event)
// {
//     EXPECT_CALL(ui, GetRequestedPower()).WillOnce(Return(800));
//     EXPECT_CALL(motor, SetPower(800));
//     EXPECT_EQ(STATE_HEATING, microwave->HandleHeatingState(EV_POWER_CHANGED));
// }

// TEST_F(TestHeatingState, test_door_opened_event)
// {
//     EXPECT_CALL(motor, SetPower(0));
//     EXPECT_CALL(ui, StopClock());
//     EXPECT_EQ(STATE_DOOR_OPENED_HEATING, microwave->HandleHeatingState(EV_DOOR_OPENED));
// }

// TEST_F(TestHeatingState, test_time_up_event)
// {
//     EXPECT_CALL(motor, SetPower(0));
//     EXPECT_CALL(ui, StopClock());
//     EXPECT_CALL(ui, Ping());
//     EXPECT_CALL(light, LightOff());
//     EXPECT_EQ(STATE_IDLE, microwave->HandleHeatingState(EV_TIME_UP));
// }


