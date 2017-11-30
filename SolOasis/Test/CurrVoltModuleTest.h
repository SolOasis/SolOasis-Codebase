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
#define MIN_CURRENT -0.05
#define MAX_CURRENT 1.5
#define MIN_VOLTAGE -0.05
#define MAX_VOLTAGE 22.0
#define MIN_POWER -0.05
#define MAX_POWER 22.0
#define MIN_ENERGY -0.05
#define MAX_ENERGY 100.0

#define PANEL_MIN_CURRENT -0.05
#define PANEL_MAX_CURRENT 1.5
#define PANEL_MIN_VOLTAGE -0.05
#define PANEL_MAX_VOLTAGE 22.0
#define PANEL_MIN_POWER -0.05
#define PANEL_MAX_POWER 22.0
#define PANEL_MIN_ENERGY -0.05
#define PANEL_MAX_ENERGY 100.0

#define BATT_MIN_CURRENT -0.05
#define BATT_MAX_CURRENT 1.5
#define BATT_MIN_VOLTAGE -0.05
#define BATT_MAX_VOLTAGE 22.0
#define BATT_MIN_POWER -0.05
#define BATT_MAX_POWER 22.0
#define BATT_MIN_ENERGY -0.05
#define BATT_MAX_ENERGY 100.0

#define CONV_MIN_CURRENT -0.05
#define CONV_MAX_CURRENT 1.5
#define CONV_MIN_VOLTAGE -0.05
#define CONV_MAX_VOLTAGE 22.0
#define CONV_MIN_POWER -0.05
#define CONV_MAX_POWER 22.0
#define CONV_MIN_ENERGY -0.05
#define CONV_MAX_ENERGY 100.0

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
