#ifndef COMMUNICATION_HANDLER_H
#define COMMUNICATION_HANDLER_H

#include <SPI.h>
#include <Ethernet.h>

#include "Arduino.h"

#define MotorCount 12

class CommunicationHandler
{
public:
    CommunicationHandler();

    void ConnectToServer();

    void RequestIsAllowed();

    // request energy zet current motor goed aan de hand van interval
    // en zet het energie op de goede index aan de hand van de current motor
    void RequestEnergy(); 

    // request local time zet local time in localTime
    void RequestLocalTime();

    // request all data zet goede data in de velden
    void RequestAllData();

    const int* GetEnergys() const;
    int GetCurrentMotor() const;
  	String GetLocalTime() const;
  	bool GetIsAllowedToRequestEnergy() const;

  	void SetIsAllowedToRequestEnergy(bool allowed);

private:
    uint8_t mac[];
    const char *server;
    const char *sas;
    const char *serviceNamespace;
    const char *hubName;
    const char *deviceName;

    EthernetClient client;
    char buffer[64];

    int energys[MotorCount];
    int currentMotor;
    String localTime;

    bool isAllowedToRequestEnergy;
};


#endif