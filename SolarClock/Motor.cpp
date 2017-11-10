#include "Motor.h"

Motor::Motor(int pin)
	: motorPin(pin)
	, length(0)
	, motorFinished(false)
{
	timer = new Timer()
}

Motor