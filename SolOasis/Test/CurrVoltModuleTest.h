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
