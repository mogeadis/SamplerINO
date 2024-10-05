/**************************************************************************************************
Filename: utilities.h

Description: This header file sets up various functionalities of the controller

Author: Alexandros Iliadis
Project: SamplerINO
Date: May 2024
**************************************************************************************************/

#ifndef UTILITIES_H
#define UTILITIES_H

// Include Libraries
#include <Arduino.h>
#include "sensors.h"
#include "midi.h"

// Define Macros
#define DEBUG 0
#define RED_PIN 3
#define GREEN_PIN 5
#define COMMON_ANODE 1
#define INTENSITY 25
#define DURATION 50

// Declare Variables
extern unsigned long timer;

// Declare Functions
void setupSerial();
void setupLED();
void controlLED();
void changeColor(byte red,byte green);
byte getAnalogValue(byte color);
void registerNotes();

#endif