/*
 * MagAccModuleTest.cpp
 *
 *  Created on: Nov 16, 2017
 *      Author: Chris
 */

#include "MagAccModuleTest.h"

TestStatus MagAccModuleTest::MagReadDataTest() {
	bool failed = false;
		int numRuns = 0;
	#if defined(DEBUG) && defined(DEBUG_TEST)
		debug.println("*** MAGNETOMETER MODULE TEST ***");
		debug.println("Printing three readings from Magnetometer Module:");
	#endif

		while(numRuns++ < NUM_RUNS){
			ma.GetMagData(&deg);
	#if defined(DEBUG) && defined(DEBUG_TEST)
			debug.print("Reading #"); debug.println(numRuns);
			debug.print("Degrees: "); debug.println(deg);
	#endif
			if(deg==lastDeg) failed = true;
		}

		return (failed)?FAIL:PASS;
}

MagAccModuleTest::MagAccModuleTest() {
	deg = 0;
	lastDeg=0;
	ma.EnableModule();
}

MagAccModuleTest::~MagAccModuleTest() {
}

void MagAccModuleTest::RunTests() {
	bool result;
		result = MagReadDataTest();
	#if defined(DEBUG) && defined(DEBUG_TEST)
		debug.print("Magnetometer read data test ");debug.println((result==PASS)?"passed!":"failed!");
	#endif
}
