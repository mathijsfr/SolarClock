#ifndef M_COMMUNICATION_HANDLER_H
#define M_COMMUNICATION_HANDLER_H

#include <gmock/gmock.h>
#include "LocalTime.h"
#include "iCommunicationHandler.h"

class mCommunicationHandler : public iCommunicationHandler
{
    public:
        MOCK_METHOD1(SetDataReceived, void(bool dataReceived));
        MOCK_METHOD1(SetDataNotReceived, void(bool dataNotReceived));
        MOCK_METHOD1(SetIsAllowedToRequestEnergy, void(bool allowed));

        MOCK_CONST_METHOD0(GetLocalTime, LocalTime());
        MOCK_CONST_METHOD0(GetNumberOfDHCPRequests, int());
        MOCK_CONST_METHOD0(GetCurrentMotor, int());
        MOCK_CONST_METHOD0(GetEnergies, const int*());
        MOCK_METHOD0(GetIsConnected, bool());
        MOCK_CONST_METHOD0(GetDataReceived, bool());
        MOCK_CONST_METHOD0(GetDataNotReceived, bool());
        MOCK_CONST_METHOD0(GetIsAllowedToRequestEnergy, bool());

        MOCK_METHOD0(Update, void());
};

#endif
