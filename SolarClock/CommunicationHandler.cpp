#include "CommunicationHandler.h"

CommunicationHandler::CommunicationHandler()
{
	for(int i = 0; i < 6; i++)
	{
		mac[i] = 0x01;
	}

	*server = "virtuedelta.database.windows.net";
	*sas = "SharedAccessSignature sr=https%3a%2f%2feventhubtest1-ns.servicebus.windows.net%2feventhubtest1%2fpublishers%2fdevice%2fmessages&sig=%2fnesMWAv9USFbjdTOewR6K8pzPr27%2fLGSCjZzrKqOeg%3d&se=1418760367&skn=SendReceiveRule";
	*serviceNamespace = "eventhubtest1-ns";
	*hubName = "eventhubtest1";
	*deviceName = "1";

	currentMotor = -1;

	isAllowedToRequestEnergy = false;
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

int CommunicationHandler::RequestIsAllowed()
{
	
}

int CommunicationHandler::RequestEnergy()
{
	
}

int CommunicationHandler::RequestLocalTime()
{
	
}

int CommunicationHandler::RequestAllData()
{
	
}
	
const int* CommunicationHandler::GetEnergies() const
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