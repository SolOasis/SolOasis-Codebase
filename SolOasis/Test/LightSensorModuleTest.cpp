/*
 * LightSensorModuleTest.cpp
 *
 *  Created on: Nov 16, 2017
 *      Author: Chris
 */

#include "LightSensorModuleTest.h"

LightSensorModuleTest::LightSensorModuleTest() {
}

LightSensorModuleTest::~LightSensorModuleTest() {
}

TestStatus LightSensorModuleTest::LightSensorReadDataTest() {
	ls.GetLightSensorData(&lsData);
#if defined(DEBUG) && defined(DEBUG_TEST)
	debug.print("Test Volt Top:    "); debug.println(lsData.voltTop);
	debug.print("Test Volt Bottom: "); debug.println(lsData.voltBottom);
	debug.print("Test Volt Left:   "); debug.println(lsData.voltLeft);
	debug.print("Test Volt Right:  "); debug.println(lsData.voltRight);
#endif

	if(lsData.voltTop < LS_VAL_MIN || lsData.voltTop > LS_VAL_MAX) return FAIL;
	if(lsData.voltBottom < LS_VAL_MIN || lsData.voltBottom > LS_VAL_MAX) return FAIL;
	if(lsData.voltRight < LS_VAL_MIN || lsData.voltRight > LS_VAL_MAX) return FAIL;
	if(lsData.voltLeft < LS_VAL_MIN || lsData.voltLeft > LS_VAL_MAX) return FAIL;

	return PASS;
}

void LightSensorModuleTest::RunTests() {
	bool result;
	result = LightSensorReadDataTest();
#if defined(DEBUG) && defined(DEBUG_TEST)
	debug.print("Light sensor value range test ");debug.println((result==PASS)?"passed!":"failed!");
#endif
}
