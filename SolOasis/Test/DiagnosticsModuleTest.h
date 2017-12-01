/*
 * DiagnosticsModuleTest.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#ifndef TEST_DIAGNOSTICSMODULETEST_H_
#define TEST_DIAGNOSTICSMODULETEST_H_

#include "Test.h"
#include "../Globals.h"
#include "../SystemStructs.h"
#include "../DiagnosticsModule.h"

#ifdef DEBUG
#include "../Debug.h"
#endif

class DiagnosticsModuleTest : public Test{
private:
#ifdef DEBUG
	Debug debug;
#endif
	DiagnosticsModule diag;
	bool setupSuccess;
	const char * requestStr = "GET / HTTP/1.1\r\nHost: desolate-depths-35197.herokuapp.com\r\nConnection: close\r\n";
	const int responseCodeSize = 3;
	TestStatus DiagnosticsServerGetTest();
	TestStatus DiagnosticsServerPostTest();
public:
	DiagnosticsModuleTest();
	~DiagnosticsModuleTest();
	void RunTests();
};


#endif /* TEST_DIAGNOSTICSMODULETEST_H_ */
