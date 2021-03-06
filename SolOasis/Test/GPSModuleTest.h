/*
 * GPSModuleTest.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#ifndef TEST_GPSMODULETEST_H_
#define TEST_GPSMODULETEST_H_

#include <time.h>
#include "Test.h"
#include "../SystemStructs.h"
#include "../GPSModule.h"

#ifdef DEBUG
#include "../Debug.h"
#endif

#define DELAY_MINUTE 	60000
#define DELAY_30SEC		30000
#define NUM_RUNS 3

class GPSModuleTest : public Test{
private:
#ifdef DEBUG
	Debug debug;
#endif
	GPSModule gps;
	GPSData gData;
	TestStatus GPSReadDataTest();
public:
	GPSModuleTest();
	~GPSModuleTest();
	void RunTests();
};



#endif /* TEST_GPSMODULETEST_H_ */
