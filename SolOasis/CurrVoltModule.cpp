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
#if defined(DEBUG) && defined(DEBUG_CV)
	debug.print("CV Data in: ");
#endif

	while(CVSerial.available()){
		c = CVSerial.read();

		((byte*)cvData)[index++] = c;

#if defined(DEBUG) && defined(DEBUG_CV)
		debug.print(c);
#endif
	}

#if defined(DEBUG) && defined(DEBUG_CV)
	debug.print("Reading #"); debug.println(numRuns);
			debug.print("Average Current:     "); debug.println(cvData.avgCurrent);
			debug.print("Average Voltage:     "); debug.println(cvData.avgVoltage);
			debug.print("Current Power:       "); debug.println(cvData.currPower);
			debug.print("Energy:   "); debug.println(cvData.energy);
#endif
	return OK;
}

