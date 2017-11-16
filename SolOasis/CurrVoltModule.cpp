/*
 * CurrVoltModule.cpp
 *
 *  Created on: Nov 9, 2017
 *      Author: Chris
 */

#include "CurrVoltModule.h"


CurrVoltModule::CurrVoltModule() {
}

CurrVoltModule::~CurrVoltModule() {
}

Status CurrVoltModule::RecieveData(CurrVoltData * cvData){
	char c;
	int index = 0;
	float data[9];
	bool id1 = false;
	bool id2 = false;
#ifdef DEBUG
	debug.print("CV Data in: ");
#endif

	while(CVSerial.available()){
		c = CVSerial.read();

		((byte*)cvData)[index++] = c;

#ifdef DEBUG
		debug.print(c);
#endif
	}

#ifdef DEBUG
	debug.print("Bytes read:        "); debug.println(index);
	debug.print("Panel Current:     "); debug.println(cvData->panelCurrent);
	debug.print("Panel Voltage:     "); debug.println(cvData->panelVoltage);
	debug.print("Panel Power:       "); debug.println(cvData->panelPower);
	debug.print("Battery Current:   "); debug.println(cvData->battCurrent);
	debug.print("Battery Voltage:   "); debug.println(cvData->battVoltage);
	debug.print("Battery Power:     "); debug.println(cvData->battPower);
	debug.print("Converter Current: "); debug.println(cvData->convCurrent);
	debug.print("Converter Voltage: "); debug.println(cvData->convVoltage);
	debug.print("Converter Power:   "); debug.println(cvData->convPower);
#endif
	return OK;
}

