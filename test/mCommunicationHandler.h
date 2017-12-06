#ifndef M_COMMUNICATION_HANDLER_H
#define M_COMMUNICATION_HANDLER_H

#include <gmock/gmock.h>
#include "iCommunicationHandler.h"

class mCommunicationHandler : public iCommunicationHandler
{
    public:
        MOCK_METHOD1(SetDataReceived, void(bool dataReceived));
        MOCK_METHOD1(SetDataNotReceived, void(bool dataNotReceived));
        MOCK_METHOD1(SetIsAllowedToRequestEnergy, void(bool allowed));

        MOCK_CONST_METHOD0(GetLocalTime, int());
        MOCK_CONST_METHOD0(GetNumberOfDHCPRequests, int());
        MOCK_CONST_METHOD0(GetCurrentMotor, int());
        MOCK_CONST_METHOD0(GetEnergies, int());
        MOCK_CONST_METHOD0(IsConnected, bool());
        MOCK_CONST_METHOD0(GetDataReceived, bool());
        MOCK_CONST_METHOD0(GetDataNotReceived, bool());
        MOCK_CONST_METHOD0(GetIsAllowedToRequestEnergy, bool());

        MOCK_METHOD1(SetWatchDogTicked, void(bool resetReadIndex));
        MOCK_METHOD0(SetWatchDogTicked, void());
        MOCK_METHOD0(SetWatchDogTicked, void());
        MOCK_METHOD0(SetWatchDogTicked, void());
        MOCK_METHOD0(SetWatchDogTicked, void());
        MOCK_METHOD0(SetWatchDogTicked, void());
};

#endif
