#ifndef COMMUNICATION_HANDLER_H
#define COMMUNICATION_HANDLER_H


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
    // uint8_t mac[];
    // const char *server;
    // const char *sas;
    // const char *serviceNamespace;
    // const char *hubName;
    // const char *deviceName;

    // //EthernetClient client;
    // char buffer[64];

    // int energys[MotorCount];
    // int currentMotor;
    // String localTime;

    // bool isAllowedToRequestEnergy;
};


#endif