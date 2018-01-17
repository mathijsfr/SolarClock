#ifndef COMMUNICATION_HANDLER_H
#define COMMUNICATION_HANDLER_H

#include "SPI.h"
#include "Ethernet.h"

#include "LocalTime.h"
#include "iCommunicationHandler.h"
#include "Timer.h"

#define MOTORCOUNT 12
#define BUFFER_SIZE 2500

#define macLength 6

class CommunicationHandler : public iCommunicationHandler
{
public:
    CommunicationHandler(byte* macAddress, String server);

    void SetDataReceived(bool dataReceived);
    void SetDataNotReceived(bool dataNotReceived);
  	void SetIsAllowedToRequestEnergy(bool allowed);

    LocalTime GetLocalTime() const;
    int GetNumberOfDHCPRequests() const;
    int GetCurrentMotor() const;
    const int* GetEnergies() const;
    bool GetIsConnected();
    bool GetDataReceived() const;
    bool GetDataNotReceived() const;
    bool GetIsAllowedToRequestEnergy();

    void Update();

private:
    bool dataReceived;
    bool dataNotReceived;

    LocalTime localTime;
    int numberOfDHCPRequests;
    int currentMotor;
    int energies[MOTORCOUNT];
    bool isAllowedToRequestEnergy;

    byte mac[macLength]; //Mac-Address Ethernet Shield
    String server;
    EthernetClient client;
    char websiteData[BUFFER_SIZE];

    void handleConnectionError();
    void readResponse();
    bool sendGetRequest();
    bool requestEnergy();
    bool requestLocalTime();

    int  getLength(int startIndex);
    String determineValue(int startIndex, int lengthOfValue);
    String filter(char* toFind, int sizeOfToFind);
};


#endif