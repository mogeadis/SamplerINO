/**************************************************************************************************
Filename: utilities.cpp

Description: This source file defines the components declared in the corresponding header file

Author: Alexandros Iliadis
Project: SamplerINO
Date: May 2024
**************************************************************************************************/

#include "utilities.h"

// Define Variables
unsigned long flash_timer = 0;

// Define Functions
void setupSerial()
{
    if(DEBUG)
	{
		Serial.begin(9600);
		while(!Serial);
		Serial.println("\n============================================================================================");
		Serial.println("                                       EXECUTING PROGRAM                                      ");
		Serial.println("============================================================================================\n");
	}
}

byte getColorValue(byte ratio)
{
    byte value;
    value = map(ratio,0,100,0,255);
    if(COMMON_ANODE)
    {
        value = 255 - value;
    }
    return value;
}

void changeColor(byte red_ratio,byte green_ratio)
{
    analogWrite(RED_PIN,getColorValue(red_ratio));
    analogWrite(GREEN_PIN,getColorValue(green_ratio));
}

void setupLED()
{
    changeColor(INTENSITY,0);
    pinMode(RED_PIN,OUTPUT);
    pinMode(GREEN_PIN,OUTPUT);
}

void flashLED()
{
    if(active_sensors > 0)
	{
		changeColor(0,INTENSITY);
		flash_timer = millis();
	}
	else
	{
		if(millis() - flash_timer >= FLASH_DURATION)
		{
			changeColor(INTENSITY,0);
		}
	}
}

void registerNotes()
{
    for(byte index = 0; index < NUM_OF_SENSORS; index++)
	{
		if(touch[index] == 1)
		{
			sendNoteOn(notes[mapping[index]]);
			touch[index] = 0;
			if(DEBUG)
			{
				Serial.print("Sensor: ");
				Serial.print(index + 1);
				Serial.print(" | Sample: ");
				Serial.print(mapping[index] + 1);
				Serial.print(" | MIDI Note On: ");
				Serial.println(notes[mapping[index]]);
			}
		}
		if(release[index] == 1)
		{
			sendNoteOff(notes[mapping[index]]);
			release[index] = 0;
			if(DEBUG)
			{
				Serial.print("Sensor: ");
				Serial.print(index + 1);
				Serial.print(" | Sample: ");
				Serial.print(mapping[index] + 1);
				Serial.print(" | MIDI Note Off: ");
				Serial.println(notes[mapping[index]]);
			}
		}
	}
}