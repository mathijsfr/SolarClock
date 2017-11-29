#include <EEPROM.h>

#include "DataHandler.h"

void DataHandler::StoreLength(Motor* motor)
{
	int length = motor->GetLength();
	char highByte = highByte(length);
	char lowByte = lowByte(length);

	EEPROM.write(motor->GetMotorPin() * 2, highByte);
	EEPROM.write((motor->GetMotorPin() * 2) + 1, lowByte);
}

void DataHandler::RetreiveLengths(Motor** motors, int count)
{
	for (int i = 0; i < count; ++i)
	{
		int length = EEPROM.read(motors[i]->GetMotorPin() * 2);
		length <<= 7;
		length |= EEPROM.read((motors[i]->GetMotorPin() * 2) + 1);

		motors[i]->SetLength(length);
	}
}