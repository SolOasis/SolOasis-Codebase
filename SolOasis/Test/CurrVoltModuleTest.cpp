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
		cv.RecieveData(&cvData);
#if defined(DEBUG) && defined(DEBUG_TEST)
		debug.print("Reading #"); debug.println(numRuns);
		debug.print("Average Current:     "); debug.println(cvData.avgCurrent);
		debug.print("Average Voltage:     "); debug.println(cvData.avgVoltage);
		debug.print("Current Power:       "); debug.println(cvData.currPower);
		debug.print("Energy:   "); debug.println(cvData.energy);

#endif
		if(cvData.avgCurrent < MIN_CURRENT || cvData.avgCurrent > MAX_CURRENT) failed = true;
		if(cvData.avgVoltage < MIN_VOLTAGE || cvData.avgVoltage > MAX_VOLTAGE) failed = true;
		if(cvData.currPower < MIN_POWER || cvData.currPower > MAX_POWER) failed = true;
		if(cvData.energy < MIN_ENERGY || cvData.energy > MAX_ENERGY) failed = true;
	}

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
