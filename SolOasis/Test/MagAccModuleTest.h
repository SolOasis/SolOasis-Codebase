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

class MagAccModuleTest : public Test{
private:
	Debug debug;
	MagAccModule ma;
	TestStatus MagReadDataTest();
public:
	MagAccModuleTest();
	~MagAccModuleTest();
	void RunTests();
};

#endif /* TEST_MAGACCMODULETEST_H_ */
