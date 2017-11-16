/*
 * Ports.cpp
 *
 *  Created on: Nov 9, 2017
 *      Author: Chris
 */

#include "Ports.h"

Uart Serial2 (&sercom1,CVSerialRXPin, CVSerialTXPin, SERCOM_RX_PAD_3, UART_TX_PAD_2);
void SERCOM1_Handler(){
	Serial2.IrqHandler();
}

void SetupPorts(){
	pinMode(GPSENPin, OUTPUT);
	pinMode(GPSFIXPin, INPUT_PULLUP);
	//pinMode(MAENPin, OUTPUT);
	pinMode(MADRDYPin, INPUT_PULLUP);
	pinMode(RotMotorPin, OUTPUT);
	pinMode(TiltMotorPin, OUTPUT);
	pinMode(RotRBSw1Pin, OUTPUT);
	pinMode(RotRBSw2Pin, OUTPUT);
	pinMode(TiltRBSw1Pin, OUTPUT);
	pinMode(TiltRBSw2Pin, OUTPUT);
	pinMode(PRTopLeftPin, INPUT_PULLUP);
	pinMode(PRTopRightPin, INPUT_PULLUP);
	pinMode(PRBottomLeftPin, INPUT_PULLUP);
	pinMode(PRBottomRightPin, INPUT_PULLUP);

	digitalWrite(GPSENPin, LOW);
	//digitalWrite(MAENPin, LOW);

	GPSSerial.begin(GPS_BAUD);
	CVSerial.begin(CV_BAUD);

	pinPeripheral(CVSerialTXPin, PIO_SERCOM);
	pinPeripheral(CVSerialRXPin, PIO_SERCOM);
}
