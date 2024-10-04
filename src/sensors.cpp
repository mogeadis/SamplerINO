/**************************************************************************************************
Filename: sensors.cpp

Description: This source file defines the components declared in the corresponding header file

Author: Alexandros Iliadis
Project: SamplerINO
Date: May 2024
**************************************************************************************************/

#include "sensors.h"

// Define Variables
Adafruit_CAP1188 modules[NUM_OF_MODULES];
const byte cs_pins[NUM_OF_MODULES] = {9,7};
const byte rst_pins[NUM_OF_MODULES] = {8,6};
byte sensor_state[NUM_OF_SENSORS] = {0};
bool touch[NUM_OF_SENSORS] = {0};
bool release[NUM_OF_SENSORS] = {0};
byte active_sensors = 0;
unsigned long trigger_timer[NUM_OF_SENSORS] = {0};

// Define Functions
void setupModules()
{
    for(byte m = 0; m < NUM_OF_MODULES; m++)
    {
        modules[m] = Adafruit_CAP1188(cs_pins[m],rst_pins[m]);
        if(modules[m].begin())
        {
            modules[m].writeRegister(CYCLE_REGISTER,CYCLE_VALUE);
            modules[m].writeRegister(SENSITIVITY_REGISTER,SENSITIVITY_VALUE);
            modules[m].writeRegister(STANDBY_REGISTER,STANDBY_VALUE);
            modules[m].writeRegister(STANDBY_SENSITIVITY_REGISTER,STANDBY_SENSITIVITY_VALUE);
            modules[m].writeRegister(CALIBRATION_REGISTER,CALIBRATION_VALUE);
            modules[m].writeRegister(RECALIBRATION_REGISTER,RECALIBRATION_VALUE);
            if(DEBUG)
            {
                Serial.print("CAP1188 Module #");
                Serial.println(m + 1);
                Serial.println("- Detection: Successful\n");
            } 
        }
        else
        {
            if(DEBUG)
            {
                Serial.print("CAP1188 Module #");
                Serial.println(m + 1);
                Serial.println("- Detection: Failed\n");
                Serial.println("CHECK CONNECTIONS AND REBOOT SYSTEM TO PROCEED");
            }
            while(true);
        }
    }
}

void detectTouch()
{
    for(byte m = 0; m < NUM_OF_MODULES; m++)
    {
        byte active_bits = modules[m].touched();   
        for(byte s = 0; s < SENSORS_PER_MODULE; s++)
        {
			byte index = m*SENSORS_PER_MODULE + s;
            if((active_bits & (1 << s)))
            {
                if(sensor_state[index] == 0)
                {
                    if((millis() - trigger_timer[index] >= TRIGGER_THRESHOLD))
			        {
                        sensor_state[index] = 1;
                        touch[index] = 1;
                        active_sensors++;
                        trigger_timer[index] = millis();
                    }
                }
            }
			else
			{
                if(sensor_state[index] == 1)
                {
                    sensor_state[index] = 0;
                    release[index] = 1;
                    active_sensors--;
                }
			}
        }
    }
}