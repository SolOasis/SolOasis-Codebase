/*
 * GPSModuleTest.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#ifndef TEST_GPSMODULETEST_H_
#define TEST_GPSMODULETEST_H_

#define MINUTE 60000

#include <time.h>
#include "Test.h"
#include "../SystemStructs.h"
#include "../GPSModule.h"
#include "../Debug.h"

class GPSModuleTest : public Test{
private:
	Debug debug;
	GPSModule gps;
	GPSData gData;
	TestStatus GPSReadDataTest();
public:
	GPSModuleTest();
	~GPSModuleTest();
	void RunTests();
};



#endif /* TEST_GPSMODULETEST_H_ */
