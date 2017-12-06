#ifndef COMMUNICATION_HANDLER_H
#define COMMUNICATION_HANDLER_H

#include "Arduino.h"

#include "SPI.h"
#include "Ethernet.h"

class CommunicationHandler
{
public:
    CommunicationHandler(byte* macAddress, String server);

    void SetDataReceived(bool dataReceived);
    void SetDataNotReceived(bool dataNotReceived);
  	void SetIsAllowedToRequestEnergy(bool allowed);

    String GetLocalTime() const;
    int GetNumberOfDHCPRequests() const;
    int GetCurrentMotor() const;
    const int* GetEnergies() const;
    bool IsConnected();
    bool GetDataReceived() const;
    bool GetDataNotReceived() const;
    bool GetIsAllowedToRequestEnergy() const;

    void ReadResponse(bool resetReadIndex);
    void RequestDHCP();
    void SendGetRequest();
    void RequestIsAllowed();
    void RequestEnergy();
    void RequestLocalTime();

private:
    #define MOTORCOUNT 12
    #define BUFFER_SIZE 2000

    bool DATA_RECEIVED;
    bool DATA_NOT_RECEIVED;

    int localTime;
    int numberOfDHCPRequests;
    int currentMotor;
    int energies[MOTORCOUNT];
    bool isAllowedToRequestEnergy;

    byte mac[6]; //Mac-Address Ethernet Shield
    String server;
    EthernetClient client;
    int readIndex;
    char websiteData[BUFFER_SIZE];

    int  getLength(int startIndex);
    String filter(char* toFind, int sizeOfToFind);
};


#endif