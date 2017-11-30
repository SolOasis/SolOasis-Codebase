/*
 * DiagnosticModuleTest.cpp
 *
 *  Created on: Nov 16, 2017
 *      Author: Chris
 */

#include "DiagnosticsModuleTest.h"

DiagnosticsModuleTest::DiagnosticsModuleTest() {
#if defined(DEBUG) && defined(DEBUG_TEST)
	debug.println("Setting up WiFi module...");
#endif
	if(diag.EnableModule() != OK) setupSuccess = false;
	else setupSuccess = true;
#if defined(DEBUG) && defined(DEBUG_TEST)
	if(setupSuccess) debug.println("WiFi successfully set up!");
	else debug.println("WiFi setup failed!");
#endif
}

DiagnosticsModuleTest::~DiagnosticsModuleTest() {
}

TestStatus DiagnosticsModuleTest::DiagnosticsServerGetTest() {
	if(!setupSuccess) return FAIL;

	String response;
	String request = String(requestStr);
	String find = "HTTP/1.1 ";

	diag.SendDiagnostics(&response, &request);
	int index = response.indexOf(find);

	if(index<0) return FAIL;
	char c = response.charAt(index+find.length());
#if defined(DEBUG) && defined(DEBUG_TEST)
	debug.print("HTTP Response Code: ");
	debug.println(response.substring((unsigned int)(index+find.length()),
			(unsigned int)(index+find.length()+responseCodeSize)).c_str());
#endif
	if(c != '2') return FAIL;

	return PASS;

}

void DiagnosticsModuleTest::RunTests() {
	bool result;
	result = DiagnosticsServerGetTest();
#if defined(DEBUG) && defined(DEBUG_TEST)
	debug.print("Diagnostics server GET test ");debug.println((result==PASS)?"passed!":"failed!");
#endif
}
