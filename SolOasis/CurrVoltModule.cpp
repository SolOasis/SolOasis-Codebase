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
#if defined(DEBUG) && defined(DEBUG_CV)
	debug.print("CV Data in: ");
#endif

	while(!CVSerial.available()){};
	while(CVSerial.available()){
		c = CVSerial.read();

		((byte*)cvData)[index++] = c;

#if defined(DEBUG) && defined(DEBUG_CV)
		debug.print(c);
#endif
	}

#if defined(DEBUG) && defined(DEBUG_CV)
			debug.print("\nAverage Current:     "); debug.println(cvData->avgCurrent);
			debug.print("Average Voltage:     "); debug.println(cvData->avgVoltage);
			debug.print("Current Power:       "); debug.println(cvData->currPower);
			debug.print("Energy:   "); debug.println(cvData->energy);
#endif
	return OK;
}

