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
		debug.print("Panel Current:     "); debug.println(cvData.panelCurrent);
		debug.print("Panel Voltage:     "); debug.println(cvData.panelVoltage);
		debug.print("Panel Power:       "); debug.println(cvData.panelPower);
		debug.print("Battery Current:   "); debug.println(cvData.battCurrent);
		debug.print("Battery Voltage:   "); debug.println(cvData.battVoltage);
		debug.print("Battery Power:     "); debug.println(cvData.battPower);
		debug.print("Converter Current: "); debug.println(cvData.convCurrent);
		debug.print("Converter Voltage: "); debug.println(cvData.convVoltage);
		debug.print("Converter Power:   "); debug.println(cvData.convPower);
#endif
		if(cvData.panelCurrent < MIN_CURRENT || cvData.panelCurrent > MAX_CURRENT) failed = true;
		if(cvData.panelVoltage < MIN_VOLTAGE || cvData.panelVoltage > MAX_VOLTAGE) failed = true;
		if(cvData.panelPower < MIN_POWER || cvData.panelPower > MAX_POWER) failed = true;
		if(cvData.battCurrent < MIN_CURRENT || cvData.battCurrent > MAX_CURRENT) failed = true;
		if(cvData.battVoltage < MIN_VOLTAGE || cvData.battVoltage > MAX_VOLTAGE) failed = true;
		if(cvData.battPower < MIN_POWER || cvData.battPower > MAX_POWER) failed = true;
		if(cvData.convCurrent < MIN_CURRENT || cvData.convCurrent > MAX_CURRENT) failed = true;
		if(cvData.convVoltage < MIN_VOLTAGE || cvData.convVoltage > MAX_VOLTAGE) failed = true;
		if(cvData.convPower < MIN_POWER || cvData.convPower > MAX_POWER) failed = true;

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
