#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include "Arduino.h"

String server("virtueusage.azurewebsites.net");
byte mac[macLength] = { 0x90, 0xA2, 0xDA, 0x0D, 0x1A, 0x6A };
MotorPins motorPins[MotorCount] = {	{ 31, 30, 29, 28 }, // motor 1
									{ 25, 24, 23, 22 }, // motor 2
									{ 6, 2, 3, 4}, // motor 3
									{ 1, 2, 3, 4 }, // motor 4
									{ 1, 2, 3, 4 }, // motor 5
									{ 1, 2, 3, 4 }, // motor 6
									{ 1, 2, 3, 4 }, // motor 7
									{ 1, 2, 3, 4 }, // motor 8
									{ 1, 2, 3, 4 }, // motor 9
									{ 1, 2, 3, 4 }, // motor 10
									{ 1, 2, 3, 4 }, // motor 11
									{ 1, 2, 3, 4 }}; // motor 12

#define MULTIPLIER 2
#define GEAR_RADIUS 2.5
#define STEPS_BAR_VISUAL 400

#endif
