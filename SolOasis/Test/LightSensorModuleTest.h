/*
 * LightSensorModuleTest.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#ifndef TEST_LIGHTSENSORMODULETEST_H_
#define TEST_LIGHTSENSORMODULETEST_H_

#include "Test.h"
#include "../Globals.h"
#include "../LightSensorModule.h"

#ifdef DEBUG
#include "../Debug.h"
#endif

#define LS_VAL_MIN -0.05
#define LS_VAL_MAX 5.0

class LightSensorModuleTest : public Test{
private:
#ifdef DEBUG
	Debug debug;
#endif
	LightSensorModule ls;
	LightSensorData lsData;

	TestStatus LightSensorReadDataTest();
public:
	LightSensorModuleTest();
	~LightSensorModuleTest();
	void RunTests();
};



#endif /* TEST_LIGHTSENSORMODULETEST_H_ */
