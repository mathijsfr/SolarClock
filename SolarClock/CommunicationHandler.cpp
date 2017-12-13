#include "CommunicationHandler.h"

CommunicationHandler::CommunicationHandler(byte* macAddress, String server)
: dataReceived(false)
, dataNotReceived(false)
, numberOfDHCPRequests(0)
, currentMotor(-1)
, isAllowedToRequestEnergy(false)
, server(server)

{
	mac[0]=macAddress[0]; mac[1]=macAddress[1];
	mac[2]=macAddress[2]; mac[3]=macAddress[3];
	mac[4]=macAddress[4]; mac[5]=macAddress[5];

	localTime.hours = 0;
	localTime.minutes = 0;
	localTime.seconds = 0;
}

void CommunicationHandler::SetDataReceived(bool dataReceived)
{
	dataReceived = dataReceived;
}

void CommunicationHandler::SetDataNotReceived(bool dataNotReceived)
{
	dataNotReceived = dataNotReceived;
}

void CommunicationHandler::SetIsAllowedToRequestEnergy(bool allowed)
{
	isAllowedToRequestEnergy = allowed;
}

LocalTime CommunicationHandler::GetLocalTime() const
{
	return localTime;
}

int CommunicationHandler::GetNumberOfDHCPRequests() const
{
	return numberOfDHCPRequests;
}

int CommunicationHandler::GetCurrentMotor() const
{
	return localTime.hours >= 12 ? localTime.hours - 12 : localTime.hours;
}

const int* CommunicationHandler::GetEnergies() const
{
	return energies;
}

bool CommunicationHandler::GetIsConnected()
{
	return client.connected();
}

bool CommunicationHandler::GetDataReceived() const
{
	return dataReceived;
}

bool CommunicationHandler::GetDataNotReceived() const
{
	return dataNotReceived;
}

bool CommunicationHandler::GetIsAllowedToRequestEnergy() const
{
	return isAllowedToRequestEnergy;
}

void CommunicationHandler::Update()
{
	if(Ethernet.begin(mac) == 1)
	{
		numberOfDHCPRequests = 0;

		if(sendGetRequest())
		{
			readResponse();
			if(RequestIsAllowed() && requestEnergy() && requestLocalTime())
			{
				dataReceived = true;
			}
		}
	}
	else
	{
		handleConnectionError();
		return;
	}

	dataNotReceived = true;
}

/* filters website data for isAllowed data */
bool CommunicationHandler::RequestIsAllowed()
{
	char isAllowedLabel [] = "<span id=\"DataList1_allowedLabel_0\">";
	String isAllowedString = filter(isAllowedLabel, sizeof(isAllowedLabel));

	if(isAllowedString != "")
	{
		if(isAllowedString == "1")
		{
			isAllowedToRequestEnergy = true;
		}
		else if(isAllowedString == "0")
		{
			isAllowedToRequestEnergy = false;
		}

		dataReceived = true;
		return true;
	}

	dataNotReceived = true;
	return false;
}

/*PRIVATE*/
/* sends get request to server */
bool CommunicationHandler::sendGetRequest()
{
	int stringLength = server.length() + 1; // +1 for \0
	
	char serverAsChar[stringLength];
	server.toCharArray(serverAsChar, stringLength);

	if (client.connect(serverAsChar, 80) == 1)
	{
		Serial.println("Connected");

		client.println("GET / HTTP/1.1");
		client.print("Host: ");
		client.println(server);
		client.println("Connection: close");
		client.println();

		return true;
	}

	return false;
}

/*PRIVATE*/
/* reads reponse data from server and fills website data */
void CommunicationHandler::readResponse()
{
	int readIndex = 0;

	while (client.available())
  	{	
	    char c = client.read();

	    websiteData[readIndex] = c;
	    websiteData[readIndex + 1] = '\0';
	    readIndex++;
  	}
}

/*PRIVATE*/
/* filters website data for energy data */
bool CommunicationHandler::requestEnergy()
{
	if(isAllowedToRequestEnergy)
	{
		bool succesful = true;

		for (int i = 1; i < 13; i++)
	    {
			int bufferSize = 22;

			if(i >= 10)
			{
				bufferSize++;
			}

			char energyLabel[bufferSize];
			sprintf(energyLabel, "<span id=\"ctl01_L_%d\">", i);

			String energieValueString = filter(energyLabel, sizeof(energyLabel));
			if (energieValueString != "")
			{
				energies[i-1] = energieValueString.toInt();
			}
			else
			{
				succesful = false;
				break;
			}
	    }

		return succesful;
	}

	return false;
}

/*PRIVATE*/
/* filters website data for local time data */
bool CommunicationHandler::requestLocalTime()
{
	char localTimeLabel[] = "<span id=\"ctl01_L_0\">";
    String localTimeString = filter(localTimeLabel, sizeof(localTimeLabel));
    
    if (localTimeString != "")
    {
      localTime.hours = (byte)localTimeString.substring(0, 2).toInt();
      localTime.minutes = (byte)localTimeString.substring(3, 5).toInt();
      localTime.seconds = (byte)localTimeString.substring(6, 8).toInt();
    }

	return false;
}

/*PRIVATE*/
/* if failed to connect 10 times, dataNotReceived will be set */
void CommunicationHandler::handleConnectionError()
{
	numberOfDHCPRequests++;

	if(numberOfDHCPRequests == 10)
	{
		dataNotReceived = true;
		numberOfDHCPRequests = 0;
	}	
}

/*PRIVATE*/
/* returns the length of the value */
int CommunicationHandler::getLength(int startIndex)
{
	int lengthOfValue = 0;

	for (int i = startIndex; i < BUFFER_SIZE; i++)
	{
		if (websiteData[i] == '<')
		{
		  return lengthOfValue;
		}
		else
		{
		  lengthOfValue++;
		}
	}

	return -1;
}

/*PRIVATE*/
/* determines the value as string and returns the value */
String CommunicationHandler::determineValue(int startIndex, int lengthOfValue)
{
	char value [lengthOfValue + 1];
	for(int i = 0; i < lengthOfValue; i++)
	{
		value[i] = websiteData[startIndex + i];
	}

	value[lengthOfValue] = '\0';

	String valueString(value);
	return valueString;
}

/*PRIVATE*/
/*extracts the value of toFind and returns the value as a string */
String CommunicationHandler::filter(char* toFind, int sizeOfToFind)
{
	int index = 0;
	sizeOfToFind = sizeOfToFind - 1; // -1 remove \0

	for (int indexText = 0; indexText < BUFFER_SIZE - sizeOfToFind; ++indexText)
	{
		if (websiteData[indexText] == toFind[index])
		{
			if (++index == sizeOfToFind)
			{
				int startIndex = indexText + 1;
				int lengthOfValue = getLength(startIndex);

				if(lengthOfValue != -1)
				{
					return determineValue(startIndex, lengthOfValue);
				}
			}
		}
		else
		{
			indexText -= index;
			index = 0;
		}
	}

	String str("");
	return str;
}