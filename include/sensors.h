/**************************************************************************************************
Filename: sensors.h

Description: This header file sets up the touch sensors of the controller

Author: Alexandros Iliadis
Project: SamplerINO
Date: May 2024
**************************************************************************************************/

#ifndef SENSORS
#define SENSORS

// Include Libraries
#include <Arduino.h>
#include <Adafruit_CAP1188.h>

// Define Macros
#define NUM_OF_MODULES 2
#define SENSORS_PER_MODULE 8
#define NUM_OF_SENSORS NUM_OF_MODULES*SENSORS_PER_MODULE
#define MAIN_REGISTER 0x00
#define SENSORS_REGISTER 0x03
#define STANDBY_REGISTER 0x40
#define STANDBY_VALUE 0b11111111
#define REPEAT_RATE_REGISTER 0x28
#define REPEAT_RATE_VALUE 0b00000000
#define CALIBRATION_REGISTER 0x26
#define CALIBRATION_VALUE 0b11111111
#define RECALIBRATION_REGISTER 0x2F
#define RECALIBRATION_VALUE 0b10011111
#define CYCLE_REGISTER 0x24
#define CYCLE_VALUE 0b0001100
#define STANDBY_CYCLE_REGISTER 0x41
#define STANDBY_CYCLE_VALUE 0b0001100
#define SENSITIVITY_REGISTER 0x1F
#define SENSITIVITY_VALUE 0b1101111
#define STANDBY_SENSITIVITY_REGISTER 0x42
#define STANDBY_SENSITIVITY_VALUE 0b110

// Declare Variables
extern Adafruit_CAP1188 modules[NUM_OF_MODULES];
extern const byte cs_pins[NUM_OF_MODULES];
extern const byte rst_pins[NUM_OF_MODULES];
extern const byte irq_pins[NUM_OF_MODULES];
extern bool sensor_state[NUM_OF_SENSORS];
extern byte active_sensors;
extern volatile bool interrupt;

// Declare Functions
void setupModules();
void handleInterrupt();

#endif