/*
 * MagAccModuleTest.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#ifndef TEST_MAGACCMODULETEST_H_
#define TEST_MAGACCMODULETEST_H_

#include <time.h>
#include "Test.h"
#include "../MagAccModule.h"
#include "../Debug.h"

#define NUM_RUNS 3

class MagAccModuleTest : public Test{
private:
	Debug debug;
	MagAccModule ma;
	double deg;
	double lastDeg;
	TestStatus MagReadDataTest();
public:
	MagAccModuleTest();
	~MagAccModuleTest();
	void RunTests();
};

#endif /* TEST_MAGACCMODULETEST_H_ */
