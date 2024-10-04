/**************************************************************************************************
Filename: midi.cpp

Description: This source file defines the components declared in the corresponding header file

Author: Alexandros Iliadis
Project: SamplerINO
Date: May 2024
**************************************************************************************************/

#include "midi.h"

// Define Variables
const byte notes[] = {36,52,55,49,38,48,47,45,42,46,44,39,51,53,56,37};
const byte mapping[] = {3,2,6,7,11,10,14,15,0,1,5,4,8,9,13,12};

// Define Functions
void sendNoteOn(byte note)
{
    midiEventPacket_t note_on = {0x09,0x90 | CHANNEL,note,VELOCITY};
    MidiUSB.sendMIDI(note_on);
}

void sendNoteOff(byte note)
{
    midiEventPacket_t note_off = {0x08,0x80 | CHANNEL,note,VELOCITY};
    MidiUSB.sendMIDI(note_off);
}

void sendData()
{
    MidiUSB.flush();
}