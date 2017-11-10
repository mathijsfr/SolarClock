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

    int ConnectToServer();

    int RequestIsAllowed();

    // request energy zet current motor goed aan de hand van interval
    // en zet het energie op de goede index aan de hand van de current motor
    int RequestEnergy(); 

    // request local time zet local time in localTime
    int RequestLocalTime();

    // request all data zet goede data in de velden
    int RequestAllData();

    const int* GetEnergies() const;
    int GetCurrentMotor() const;
  	String GetLocalTime() const;
  	bool GetIsAllowedToRequestEnergy() const;

  	void SetIsAllowedToRequestEnergy(bool allowed);

private:
    byte mac[6];
    char *server;
    char *sas;
    char *serviceNamespace;
    char *hubName;
    char *deviceName;

    EthernetClient client;
    char buffer[64];

    int energys[MotorCount];
    int currentMotor;
    String localTime;

    bool isAllowedToRequestEnergy;
};


#endif