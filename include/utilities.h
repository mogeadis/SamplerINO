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
#define FLASH_DURATION 50
#define INTENSITY 25

// Declare Variables
extern unsigned long flash_timer;

// Declare Functions
void setupSerial();
byte getColorValue(byte percentage);
void changeColor(byte red,byte green);
void setupLED();
void flashLED();
void registerNotes();

#endif