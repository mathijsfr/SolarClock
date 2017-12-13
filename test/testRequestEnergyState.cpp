#include "SolarClock.h"

#include "mBarHandler.h"
#include "mCommunicationHandler.h"
#include "mWatchDogTimer.h"

using ::testing::Return;
using ::testing::ReturnPointee;
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

TEST_F(TestRequestEnergyState, test_data_received_event)
{
    EXPECT_CALL(communicationHandler, SetIsAllowedToRequestEnergy(false));

    EXPECT_CALL(communicationHandler, GetCurrentMotor()).WillOnce(Return(0));
    EXPECT_CALL(barHandler, ResetBar(0));

    int energie[MotorCount];
    EXPECT_CALL(communicationHandler, GetEnergies()).WillOnce(ReturnPointee(&energie));
    EXPECT_CALL(barHandler, CalculateSteps(energie[0])).WillOnce(Return(90));

    EXPECT_CALL(barHandler, SetBar(0, 90));

    EXPECT_CALL(communicationHandler, GetLocalTime()).WillOnce(Return(12));
    EXPECT_CALL(watchDogTimer, CalculateWatchDog(12));
    EXPECT_CALL(watchDogTimer, EnableWatchDog());

    EXPECT_EQ(State_WatchDogHandling, solarClock->HandleRequestEnergyState(EV_DATA_RECEIVED));
}

TEST_F(TestRequestEnergyState, test_data_not_received_event)
{
    EXPECT_CALL(communicationHandler, SetIsAllowedToRequestEnergy(false));
    EXPECT_CALL(barHandler, ResetBars(MotorCount));

    EXPECT_EQ(State_InitializeClock, solarClock->HandleRequestEnergyState(EV_DATA_NOT_RECEIVED));
}

TEST_F(TestRequestEnergyState, test_time_up_event_allowed_false)
{
    EXPECT_CALL(communicationHandler, GetIsAllowedToRequestEnergy()).WillOnce(Return(false));
    EXPECT_CALL(communicationHandler, RequestIsAllowed());

    EXPECT_EQ(State_RequestEnergy, solarClock->HandleRequestEnergyState(EV_TIME_UP));
}

TEST_F(TestRequestEnergyState, test_time_up_event_allowed_true)
{
    EXPECT_CALL(communicationHandler, GetIsAllowedToRequestEnergy()).WillOnce(Return(true));

    EXPECT_CALL(communicationHandler, Update());

    EXPECT_EQ(State_RequestEnergy, solarClock->HandleRequestEnergyState(EV_TIME_UP));
}

