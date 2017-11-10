#include "CommunicationHandler.h"

CommunicationHandler::CommunicationHandler()
: DATA_RECEIVED(false)
	, DATA_NOT_RECEIVED(false)
	, numberOfDHCPRequests(0)
	, server("virtuedelta.database.windows.net")
	, sas("SharedAccessSignature sr=https%3a%2f%2feventhubtest1-ns.servicebus.windows.net%2feventhubtest1%2fpublishers%2fdevice%2fmessages&sig=%2fnesMWAv9USFbjdTOewR6K8pzPr27%2fLGSCjZzrKqOeg%3d&se=1418760367&skn=SendReceiveRule")
	, serviceNamespace("eventhubtest1-ns")
	, hubName("eventhubtest1")
	, deviceName("1")
	, currentMotor(-1)
	, isAllowedToRequestEnergy(false)
	, localTime("")
{
	mac[0]=0x01; mac[1]=0x01; mac[2]=0x01; mac[3]=0x01; mac[4]=0x01; mac[5]=0x01;
}

void CommunicationHandler::SetDataReceived(bool dataReceived)
{
	DATA_RECEIVED = dataReceived;
}

void CommunicationHandler::SetDataNotReceived(bool dataNotReceived)
{
	DATA_NOT_RECEIVED = dataNotReceived;
}

void CommunicationHandler::SetIsAllowedToRequestEnergy(bool allowed)
{

}

bool CommunicationHandler::GetDataReceived() const
{
	return DATA_RECEIVED;
}

bool CommunicationHandler::GetDataNotReceived() const
{
	return DATA_NOT_RECEIVED;
}

int CommunicationHandler::GetNumberOfIPRequests() const
{

}

const int* CommunicationHandler::GetEnergies() const
{
	
}

void CommunicationHandler::GetCurrentMotor() const
{

}

String CommunicationHandler::GetLocalTime() const
{

}

bool CommunicationHandler::GetIsAllowedToRequestEnergy() const
{

}

void CommunicationHandler::RequestDHCP()
{
	if(Ethernet.begin(mac) == 1)
	{
		DATA_RECEIVED = true;
		numberOfDHCPRequests = 0;
	}
	else
	{
		numberOfDHCPRequests++;

		if(numberOfDHCPRequests == 10)
		{
			DATA_NOT_RECEIVED = true;
		}
	}
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