/*
 * CurrVoltModule.cpp
 *
 *  Created on: Nov 9, 2017
 *      Author: Chris
 */

#include "CurrVoltModule.h"

//**************************************************************************************
// ~Current-Voltage Module Constructor~
//**************************************************************************************
CurrVoltModule::CurrVoltModule() {

}
//**************************************************************************************


//**************************************************************************************
// ~Current-Voltage Module Destructor~
//**************************************************************************************
CurrVoltModule::~CurrVoltModule() {

}
//**************************************************************************************


//**************************************************************************************
// ~Receive Serial CV Data~
// Listens to CV serial port for sent data
//**************************************************************************************
Status CurrVoltModule::ReceiveData(CurrVoltData * cvData){
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
	debug.println();
	debug.print("Average Current:     "); debug.println(cvData->avgCurrent);
	debug.print("Average Voltage:     "); debug.println(cvData->avgVoltage);
	debug.print("Current Power:       "); debug.println(cvData->currPower);
	debug.print("Energy:   "); debug.println(cvData->energy);
//	debug.println();
//	debug.print("Panel Average Current:     "); debug.println(cvData->panelAvgCurrent);
//	debug.print("Panel Average Voltage:     "); debug.println(cvData->panelAvgVoltage);
//	debug.print("Panel Current Power:       "); debug.println(cvData->panelCurrPower);
//	debug.print("Panel Energy:              "); debug.println(cvData->panelEnergy);
//	debug.print("Battery Average Current:   "); debug.println(cvData->battAvgCurrent);
//	debug.print("Battery Average Voltage:   "); debug.println(cvData->battAvgVoltage);
//	debug.print("Battery Current Power:     "); debug.println(cvData->battCurrPower);
//	debug.print("Battery Energy:            "); debug.println(cvData->battEnergy);
//	debug.print("Converter Average Current: "); debug.println(cvData->convAvgCurrent);
//	debug.print("Converter Average Voltage: "); debug.println(cvData->convAvgVoltage);
//	debug.print("Converter Current Power:   "); debug.println(cvData->convCurrPower);
//	debug.print("Converter Energy:          "); debug.println(cvData->convEnergy);
#endif
	return OK;
}
//**************************************************************************************

