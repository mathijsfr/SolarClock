#include "DataHandler.h"

void DataHandler::StoreLength(Motor* motor)
{
	int steps = motor->GetSteps();
	char highByte = (char)steps;
	char lowByte = (char)(steps << 7);

	EEPROM.write(motor->GetMotorPin(), highByte);
	EEPROM.write(motor->GetMotorPin() + 1, lowByte);
}

void DataHandler::RetreiveLengths(Motor** motors, int count)
{
	for (int i = 0; i < count; ++i)
	{
		int length = EEPROM.read(motors[i]->GetMotorPin());
		length <<= 7;
		length |= EEPROM.read(motors[i]->GetMotorPin() + 1);

		motors[i]->SetSteps(length);
	}
}