/*
 * CurrVoltModuleTest.cpp
 *
 *  Created on: Nov 16, 2017
 *      Author: Chris
 */

#include "CurrVoltModuleTest.h"

TestStatus CurrVoltModuleTest::CVReadDataTest() {
	bool failed = false;
	int numRuns = 0;
#if defined(DEBUG) && defined(DEBUG_TEST)
	debug.println("*** CURRENT-VOLTAGE MODULE TEST ***");
	debug.println("Printing three readings from CV Module:");
#endif

	while(numRuns++ < NUM_RUNS){
		cv.ReceiveData(&cvData);
#if defined(DEBUG) && defined(DEBUG_TEST)
		debug.print("Reading #"); debug.println(numRuns);
		debug.print("Average Current:     "); debug.println(cvData.avgCurrent);
		debug.print("Average Voltage:     "); debug.println(cvData.avgVoltage);
		debug.print("Current Power:       "); debug.println(cvData.currPower);
		debug.print("Energy:   "); debug.println(cvData.energy);
//		debug.print("Panel Average Current:     "); debug.println(cvData.panelAvgCurrent);
//		debug.print("Panel Average Voltage:     "); debug.println(cvData.panelAvgVoltage);
//		debug.print("Panel Current Power:       "); debug.println(cvData.panelCurrPower);
//		debug.print("Panel Energy:              "); debug.println(cvData.panelEnergy);
//		debug.print("Battery Average Current:   "); debug.println(cvData.battAvgCurrent);
//		debug.print("Battery Average Voltage:   "); debug.println(cvData.battAvgVoltage);
//		debug.print("Battery Current Power:     "); debug.println(cvData.battCurrPower);
//		debug.print("Battery Energy:            "); debug.println(cvData.battEnergy);
//		debug.print("Converter Average Current: "); debug.println(cvData.convAvgCurrent);
//		debug.print("Converter Average Voltage: "); debug.println(cvData.convAvgVoltage);
//		debug.print("Converter Current Power:   "); debug.println(cvData.convCurrPower);
//		debug.print("Converter Energy:          "); debug.println(cvData.convEnergy);

#endif
		if(cvData.avgCurrent < MIN_CURRENT || cvData.avgCurrent > MAX_CURRENT) {
			failed = true;
			debug.print("-->Failed: avgCurrent range invalid:"); debug.println(cvData.avgCurrent);
		}
		if(cvData.avgVoltage < MIN_VOLTAGE || cvData.avgVoltage > MAX_VOLTAGE) {
			failed = true;
			debug.print("-->Failed: avgVoltage range invalid:"); debug.println(cvData.avgVoltage);
		}
		if(cvData.currPower < MIN_POWER || cvData.currPower > MAX_POWER) {
			failed = true;
			debug.print("-->Failed: currPower range invalid:"); debug.println(cvData.currPower);
		}
		if(cvData.energy < MIN_ENERGY || cvData.energy > MAX_ENERGY) {
			failed = true;

			debug.print("-->Failed: energy range invalid:"); debug.println(cvData.energy);
		}
	}
	debug.print("failed:"); debug.println(failed);
	return (failed)?FAIL:PASS;
}

CurrVoltModuleTest::CurrVoltModuleTest() {
}

CurrVoltModuleTest::~CurrVoltModuleTest() {
	memset(&cvData,0,sizeof(CurrVoltData));
}

void CurrVoltModuleTest::RunTests() {
	bool result;
	result = CVReadDataTest();
#if defined(DEBUG) && defined(DEBUG_TEST)
	debug.print("Current-Voltage read data test ");debug.println((result==PASS)?"passed!":"failed!");
#endif
}
