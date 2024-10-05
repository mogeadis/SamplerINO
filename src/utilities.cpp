/**************************************************************************************************
Filename: utilities.cpp

Description: This source file defines the components declared in the corresponding header file

Author: Alexandros Iliadis
Project: SamplerINO
Date: May 2024
**************************************************************************************************/

#include "utilities.h"

// Define Variables
unsigned long timer = 0;

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

void setupLED()
{
    pinMode(RED_PIN,OUTPUT);
    pinMode(GREEN_PIN,OUTPUT);
    changeColor(INTENSITY,0);
}

void changeColor(byte red,byte green)
{
    analogWrite(RED_PIN,getAnalogValue(red));
    analogWrite(GREEN_PIN,getAnalogValue(green));
}

byte getAnalogValue(byte color)
{
    byte value;
    value = map(color,0,100,0,255);
    if(COMMON_ANODE)
    {
        value = 255 - value;
    }
    return value;
}

void controlLED()
{
    if(active_sensors > 0)
	{
		active_sensors == 1 ? changeColor(INTENSITY,INTENSITY) : changeColor(0,INTENSITY);
		timer = millis();
	}
	else
	{
		if(millis() - timer >= DURATION)
		{
			changeColor(INTENSITY,0);
		}
	}
}

void registerNotes()
{
    for(byte m = 0; m < NUM_OF_MODULES; m++)
    {
        modules[m].writeRegister(MAIN_REGISTER,modules[m].readRegister(MAIN_REGISTER) & ~1);
        byte active_bits = modules[m].readRegister(SENSORS_REGISTER);
        for(byte s = 0; s < SENSORS_PER_MODULE; s++)
        {
            byte index = m*SENSORS_PER_MODULE + s;
            if((active_bits & (1 << s)))
            {
                if(sensor_state[index] == 0)
                {
                    sendNoteOn(notes[mapping[index]]);
                    sensor_state[index] = 1;
                    active_sensors++;
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
            }
            else
            {
                if(sensor_state[index] == 1)
                {
                    sendNoteOff(notes[mapping[index]]);
                    sensor_state[index] = 0;
                    active_sensors--;
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
    }
}