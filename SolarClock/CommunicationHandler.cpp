#include "CommunicationHandler.h"

CommunicationHandler::CommunicationHandler()
{
	mac = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
	server = "virtuedelta.database.windows.net";
	sas = "SharedAccessSignature sr=https%3a%2f%2feventhubtest1-ns.servicebus.windows.net%2feventhubtest1%2fpublishers%2fdevice%2fmessages&sig=%2fnesMWAv9USFbjdTOewR6K8pzPr27%2fLGSCjZzrKqOeg%3d&se=1418760367&skn=SendReceiveRule";
	serviceNamespace = "eventhubtest1-ns"
	hubName = "eventhubtest1";
	deviceName = "1";

	currentMotor = -1;
	localTime = NULL;
	isAllowedtoRequestEnergy = false;
}

int CommunicationHandler::ConnectToServer()
{

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