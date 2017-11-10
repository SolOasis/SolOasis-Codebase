#ifndef _PORTS_H_
#define _PORTS_H_

#include <Arduino.h>
#include <HardwareSerial.h>
#include "wiring_private.h"

#define GPSENPin 15
#define GPSFIXPin 14
#define MADRDYPin 9
#define MAINT1Pin 10
#define RotMotorPin 5
#define TiltMotorPin 6
#define RotRBSw1Pin 24
#define RotRBSw2Pin 23
#define TiltRBSw1Pin 12
#define TiltRBSw2Pin 13
#define PRTopPin A2
#define PRBottomPin A3
#define PRLeftPin A4
#define PRRightPin A5

#define CVSerialTXPin 10
#define CVSerialRXPin 12

// Must define Serial2 in Ports.cpp to avoid
// redefinition every time Ports.h is included
extern Uart Serial2;

#define GPSSerial Serial1
#define CVSerial Serial2

#define GPS_BAUD 9600
#define CV_BAUD 9600

// Define SetupPorts() as extern to avoid compiling
// problems
extern void SetupPorts();

#endif /* _PORTS_H_ */
