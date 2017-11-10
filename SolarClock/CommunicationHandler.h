#ifndef COMMUNICATION_HANDLER_H
#define COMMUNICATION_HANDLER_H

#include "Ethernet.h"
#include "SPI.h"
#include "Arduino.h"

#define MotorCount 12

class CommunicationHandler
{
public:
    CommunicationHandler();

    void SetDataReceived(bool dataReceived);
    void SetDataNotReceived(bool dataNotReceived);
    
  	void SetIsAllowedToRequestEnergy(bool allowed);

    bool GetDataReceived() const;
    bool GetDataNotReceived() const;

    int GetNumberOfIPRequests() const;
    const int* GetEnergies() const;
    void GetCurrentMotor() const;
    String GetLocalTime() const;
    bool GetIsAllowedToRequestEnergy() const;

    void RequestDHCP();
    void RequestIsAllowed();
           
    void RequestEnergy(); /* request energy zet current motor goed aan de hand van interval
                             en zet het energie op de goede index aan de hand van de current motor */
    void RequestLocalTime();    /* request local time zet local time in localTime */
    void RequestAllData(); /* request all data zet goede data in de velden */


private:
    bool DATA_RECEIVED;
    bool DATA_NOT_RECEIVED;

    int numberOfDHCPRequests;

    byte mac[6];
    char server;
    char sas;
    char serviceNamespace;
    char hubName;
    char deviceName;
    EthernetClient client;

    int energys[MotorCount];
    int currentMotor;
    bool isAllowedToRequestEnergy;
    String localTime;
};


#endif