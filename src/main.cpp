/**************************************************************************************************
Filename: main.cpp

Description: This source file sets up the core functionality of the controller

Author: Alexandros Iliadis
Project: SamplerINO
Date: May 2024
**************************************************************************************************/

#include <Arduino.h>
#include "utilities.h"
#include "sensors.h"
#include "midi.h"

void setup()
{
	setupSerial();
	setupLED();
	setupModules();
}

void loop()
{
	detectTouch();
	registerNotes();
	sendData();
	flashLED();
}