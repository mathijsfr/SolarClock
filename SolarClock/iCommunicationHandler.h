#ifndef I_COMMUNICATION_HANDLER_H
#define I_COMMUNICATION_HANDLER_H

#include "Arduino.h"

class iCommunicationHandler
{
public:
    virtual void SetDataReceived(bool dataReceived) = 0;
    virtual void SetDataNotReceived(bool dataNotReceived) = 0;
  	virtual void SetIsAllowedToRequestEnergy(bool allowed) = 0;

    virtual int GetLocalTime() const = 0;
    virtual int GetNumberOfDHCPRequests() const = 0;
    virtual int GetCurrentMotor() const = 0;
    virtual const int* GetEnergies() const = 0;
    virtual bool IsConnected() = 0;
    virtual bool GetDataReceived() const = 0;
    virtual bool GetDataNotReceived() const = 0;
    virtual bool GetIsAllowedToRequestEnergy() const = 0;

    virtual void ReadResponse(bool resetReadIndex) = 0;
    virtual void RequestDHCP() = 0;
    virtual void SendGetRequest() = 0;
    virtual void RequestIsAllowed() = 0;
    virtual void RequestEnergy() = 0;
    virtual void RequestLocalTime() = 0;

};


#endif