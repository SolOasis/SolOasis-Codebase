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

class LightSensorModuleTest : public Test{
private:
#ifdef DEBUG
	Debug debug;
#endif
	LightSensorModule ls;
public:
	LightSensorModuleTest();
	~LightSensorModuleTest();
	void RunTests();
};



#endif /* TEST_LIGHTSENSORMODULETEST_H_ */
