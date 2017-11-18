/*
 * DiagnosticModuleTest.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#ifndef TEST_DIAGNOSTICSMODULETEST_H_
#define TEST_DIAGNOSTICSMODULETEST_H_

#include "Test.h"
#include "../Globals.h"
#include "../DiagnosticsModule.h"

#ifdef DEBUG
#include "Debug.h"
#endif

class DiagnosticsModuleTest : public Test{
private:
#ifdef DEBUG
	Debug debug;
#endif
	DiagnosticsModule diag;
public:
	DiagnosticsModuleTest();
	~DiagnosticsModuleTest();
	void RunTests();
};


#endif /* TEST_DIAGNOSTICSMODULETEST_H_ */
