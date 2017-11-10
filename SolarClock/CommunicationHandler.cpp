#include <SPI.h>
#include <Ethernet.h>

#include "Arduino.h"
#include "CommunicationHandler.h"

CommunicationHandler::CommunicationHandler()
{
	mac = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
	*server = "virtuedelta.database.windows.net";
	*sas = "SharedAccessSignature sr=https%3a%2f%2feventhubtest1-ns.servicebus.windows.net%2feventhubtest1%2fpublishers%2fdevice%2fmessages&sig=%2fnesMWAv9USFbjdTOewR6K8pzPr27%2fLGSCjZzrKqOeg%3d&se=1418760367&skn=SendReceiveRule";
	*serviceNamespace = "eventhubtest1-ns"
	*hubName = "eventhubtest1";
	*deviceName = "1";
}

int CommunicationHandler::ConnectToServer()
{
	int returnValue = 0;

	if(Ethernet.begin(mac) == 1) //begin() returns 1 if connection succeeded
	{
		returnValue = client.connect(server, 80); //connect() returns 1 if succeeded
	}
	
	return returnValue;
}

void CommunicationHandler::RequestIsAllowed()
{

}

void CommunicationHandler::RequestEnergy()
{

}

void CommunicationHandler::RequestLocalTime()
{

}

void CommunicationHandler::RequestAllData()
{

}
	
const int* CommunicationHandler::GetEnergys() const
{

}

int CommunicationHandler::GetCurrentMotor() const
{

}

String CommunicationHandler::GetLocalTime() const
{

}

bool CommunicationHandler::GetIsAllowedToRequestEnergy() const
{

}

void CommunicationHandler::SetIsAllowedToRequestEnergy(bool allowed)
{

}