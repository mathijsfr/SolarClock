#include "SolarClock.h"

#include "mBarHandler.h"
#include "mCommunicationHandler.h"
#include "mWatchDogTimer.h"

using ::testing::Return;
using ::testing::ReturnPointee;
using ::testing::SetArrayArgument;
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

TEST_F(TestInitializeClockState, test_clock_initialized_event)
{
    EXPECT_EQ(State_RequestEnergy, solarClock->HandleInitializeClockState(EV_CLOCK_INITIALIZED));
}

TEST_F(TestInitializeClockState, test_data_received_event)
{
    int steps[MotorCount];
    int energies[MotorCount];

    EXPECT_CALL(communicationHandler, GetEnergies())
        .WillOnce(ReturnPointee(&energies));

    EXPECT_CALL(barHandler, CalculateSteps(energies, steps, MotorCount)).WillOnce(SetArrayArgument<1>(steps, steps + MotorCount)); // ?
    EXPECT_CALL(barHandler, SetBars(steps, MotorCount));

    EXPECT_EQ(State_InitializeClock, solarClock->HandleInitializeClockState(EV_DATA_RECEIVED));
}
