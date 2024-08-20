/**************************************************************************************************
Filename: midi.h

Description: This header file sets up the MIDI communication of the controller

Author: Alexandros Iliadis
Project: SamplerINO
Date: May 2024
**************************************************************************************************/

#ifndef MIDI_H
#define MIDI_H

// Include Libraries
#include <Arduino.h>
#include <MIDIUSB.h>

// Define Macros
#define CHANNEL 0
#define VELOCITY 100

// Declare Variables
extern const byte notes[];
extern const byte mapping[];

// Declare Functions
void sendNoteOn(byte note);
void sendNoteOff(byte note);
void sendData();

#endif