#ifndef I_COMMUNICATION_HANDLER_H
#define I_COMMUNICATION_HANDLER_H

#include "Arduino.h"
#include "LocalTime.h"

class iCommunicationHandler
{
public:
    virtual void SetDataReceived(bool dataReceived) = 0;
    virtual void SetDataNotReceived(bool dataNotReceived) = 0;
  	virtual void SetIsAllowedToRequestEnergy(bool allowed) = 0;

    virtual LocalTime GetLocalTime() const = 0;
    virtual int GetNumberOfDHCPRequests() const = 0;
    virtual int GetCurrentMotor() const = 0;
    virtual const int* GetEnergies() const = 0;
    virtual bool GetIsConnected() = 0;
    virtual bool GetDataReceived() const = 0;
    virtual bool GetDataNotReceived() const = 0;
    virtual bool GetIsAllowedToRequestEnergy() const = 0;

    virtual void Update() = 0;
    virtual bool RequestIsAllowed() = 0;

};


#endif