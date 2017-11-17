/*
 * CurrVoltModuleTest.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#ifndef TEST_CURRVOLTMODULETEST_H_
#define TEST_CURRVOLTMODULETEST_H_

#include <time.h>
#include "Test.h"
#include "../SystemStructs.h"
#include "../CurrVoltModule.h"
#include "../Debug.h"

#define NUM_RUNS 3
#define MIN_CURRENT 0.001
#define MAX_CURRENT 10.0
#define MIN_VOLTAGE 0.001
#define MAX_VOLTAGE 24.0
#define MIN_POWER 0.001
#define MAX_POWER 100

class CurrVoltModuleTest : public Test{
private:
	Debug debug;
	CurrVoltModule cv;
	CurrVoltData cvData;
	TestStatus CVReadDataTest();
public:
	CurrVoltModuleTest();
	~CurrVoltModuleTest();
	void RunTests();
};



#endif /* TEST_CURRVOLTMODULETEST_H_ */
