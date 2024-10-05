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
extern const byte irq_pins[NUM_OF_MODULES] = {1,0};
bool sensor_state[NUM_OF_SENSORS] = {0};
byte active_sensors = 0;
volatile bool interrupt = false;

// Define Functions
void setupModules()
{
    for(byte m = 0; m < NUM_OF_MODULES; m++)
    {
        modules[m] = Adafruit_CAP1188(cs_pins[m],rst_pins[m]);
        if(modules[m].begin())
        {
            pinMode(irq_pins[m],INPUT_PULLUP);
            attachInterrupt(digitalPinToInterrupt(irq_pins[m]),handleInterrupt,FALLING);
            modules[m].writeRegister(STANDBY_REGISTER,STANDBY_VALUE);
            modules[m].writeRegister(REPEAT_RATE_REGISTER,REPEAT_RATE_VALUE);
            modules[m].writeRegister(CALIBRATION_REGISTER,CALIBRATION_VALUE);
            modules[m].writeRegister(RECALIBRATION_REGISTER,RECALIBRATION_VALUE);
            modules[m].writeRegister(CYCLE_REGISTER,CYCLE_VALUE);
            modules[m].writeRegister(STANDBY_CYCLE_REGISTER,STANDBY_CYCLE_VALUE);
            modules[m].writeRegister(SENSITIVITY_REGISTER,SENSITIVITY_VALUE);
            modules[m].writeRegister(STANDBY_SENSITIVITY_REGISTER,STANDBY_SENSITIVITY_VALUE);
            Serial.print("CAP1188 Module #");
            Serial.println(m + 1);
            Serial.println("- Detection: Successful\n");
        }
        else
        {
            Serial.print("CAP1188 Module #");
            Serial.println(m + 1);
            Serial.println("- Detection: Failed\n");
            Serial.println("CHECK CONNECTIONS AND REBOOT SYSTEM TO PROCEED");
            while(true);
        }
    }
}

void handleInterrupt()
{
    interrupt = true;
}