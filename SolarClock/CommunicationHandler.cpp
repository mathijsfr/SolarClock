#include "CommunicationHandler.h"

CommunicationHandler::CommunicationHandler(byte* macAddress, String server)
: DATA_RECEIVED(false)
, DATA_NOT_RECEIVED(false)
, localTime(-1)
, numberOfDHCPRequests(0)
, currentMotor(-1)
, isAllowedToRequestEnergy(false)
, server(server)
, readIndex(0)

{
	mac[0]=macAddress[0]; mac[1]=macAddress[1];
	mac[2]=macAddress[2]; mac[3]=macAddress[3];
	mac[4]=macAddress[4]; mac[5]=macAddress[5];
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
	isAllowedToRequestEnergy = allowed;
}

String CommunicationHandler::GetLocalTime() const
{
	return localTime;
}

int CommunicationHandler::GetNumberOfDHCPRequests() const
{
	return numberOfDHCPRequests;
}

int CommunicationHandler::GetCurrentMotor() const
{
	return currentMotor;
}

const int* CommunicationHandler::GetEnergies() const
{
	return energies;
}

bool CommunicationHandler::IsConnected()
{
	return client.connected();
}

bool CommunicationHandler::GetDataReceived() const
{
	return DATA_RECEIVED;
}

bool CommunicationHandler::GetDataNotReceived() const
{
	return DATA_NOT_RECEIVED;
}

bool CommunicationHandler::GetIsAllowedToRequestEnergy() const
{
	return isAllowedToRequestEnergy;
}

/* requests DHCP from router*/
/* if successful => DATA_RECEIVED = true, else DATA_NOT_RECEIVED = true */
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

/* sends get request to server */
void CommunicationHandler::SendGetRequest()
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

		DATA_RECEIVED = true;
	}
	else
	{
		DATA_NOT_RECEIVED = true;
	}
}

/* reads reponse data from server and fills website data */
void CommunicationHandler::ReadResponse(bool resetReadIndex)
{
	if(resetReadIndex)
	{
		readIndex = 0;
	}

	while (client.available())
  	{	
	    char c = client.read();

	    websiteData[readIndex] = c;
	    websiteData[readIndex + 1] = '\0';
	    readIndex++;
  	}

  	DATA_RECEIVED = true;
}

/* filters website data for isAllowed data */
void CommunicationHandler::RequestIsAllowed()
{
	char isAllowedLabel [] = "<span id=\"DataList1_allowedLabel_0\">";
	String isAllowedString = filter(isAllowedLabel, sizeof(isAllowedLabel));

	if(isAllowedString == "1")
	{
		isAllowedToRequestEnergy = true;
	}
	else if(isAllowedString == "0")
	{
		isAllowedToRequestEnergy = false;
	}
}

/* filters website data for energy data */
void CommunicationHandler::RequestEnergy()
{
	if(isAllowedToRequestEnergy)
	{
		char energyLabel[] = "<span id=\"DataList1_wHLabel_0\">";
		String energiesString = filter(energyLabel, sizeof(energyLabel));

		if(energiesString != "")
		{
			int energiesHours[MOTORCOUNT];
			int energiesStringLength = energiesString.length();

			int index = 0;
			int position = 0;
			for(int i = 0; i <= energiesStringLength; i++)
			{
				if(energiesString[i] == ',')
				{
					energiesHours[index] = energiesString.substring(position, i).toInt();
					index = index + 1;
					position = i + 1;
				}
			}

			RequestLocalTime();

			
		}
	}
}

/* filters website data for local time data */
void CommunicationHandler::RequestLocalTime()
{
	String localTime("localtime");
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
/*returns the string of the value */
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
					char value [lengthOfValue + 1];
					for(int i = 0; i < lengthOfValue; i++)
					{
						value[i] = websiteData[startIndex + i];
					}

					value[lengthOfValue] = '\0';

					String valueString(value);
					return valueString;
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