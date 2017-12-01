/*
 * DiagnosticModuleTest.cpp
 *
 *  Created on: Nov 16, 2017
 *      Author: Chris
 */

#include "DiagnosticsModuleTest.h"

static Status CreatePostString(String * post, GPSData* gData,
		CurrVoltData* cvData, SpaData* sData, double deg) {

	// setup json object for server to read
	String json = String("");
	json +="{\"ID\": "; json+=STATION_ID; json+=", \"data\":{";
	json+="\""; json+=GPS_HOUR_ID; json+="\": "; json+=String((int)gData->hour); json+=", ";
	json+="\""; json+=GPS_MIN_ID; json+="\": "; json+=String((int)gData->minute); json+=", ";
	json+="\""; json+=GPS_SEC_ID; json+="\": "; json+=String((int)gData->second); json+=", ";
	json+="\""; json+=GPS_DAY_ID; json+="\": "; json+=String((int)gData->day); json+=", ";
	json+="\""; json+=GPS_MONTH_ID; json+="\": "; json+=String((int)gData->month); json+=", ";
	json+="\""; json+=GPS_YEAR_ID; json+="\": "; json+=String((int)gData->year); json+=", ";
	json+="\""; json+=GPS_LAT_ID; json+="\": "; json+=String(gData->latitude); json+=", ";
	json+="\""; json+=GPS_LONG_ID; json+="\": "; json+=String(gData->longitude); json+=", ";
	json+="\""; json+=GPS_ALT_ID; json+="\": "; json+=String(gData->altitude); json+="}}\r\n";

	// put POST string together
	*post+="POST "; *post+=PATH; *post+=" HTTP/1.1\r\nHost: "; *post+=SERVER; *post+="\r\nContent-Type: application/json\r\nContent-Length: "
			+ String(json.length()); *post+="\r\n\r\n"; *post+=json;

	return OK;
}

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

TestStatus DiagnosticsModuleTest::DiagnosticsServerPostTest() {
	GPSData gData;
	CurrVoltData cvData;
	SpaData sData;
	double deg = 123.456;
	String post, response;
	String find = "HTTP/1.1 ";

	gData.hour = 0;
	gData.minute = 12;
	gData.second = 34;
	gData.day = 7;
	gData.month = 12;
	gData.year = 2017;
	gData.latitude = 40.443651;
	gData.longitude = -79.958767;

	sData.azimuth = 0;
	sData.elevation = 0;
	sData.julianDay = 0;
	sData.sunrise = 0;
	sData.sunset = 0;
	sData.zenith = 0;

//	cvData.panelAvgVoltage = 1.0;
//	cvData.panelAvgCurrent = 2.0;
//	cvData.panelCurrPower = 3.0;
//	cvData.panelEnergy = 4.0;
//	cvData.battAvgVoltage = 1.1;
//	cvData.battAvgCurrent = 2.1;
//	cvData.battCurrPower = 3.1;
//	cvData.battEnergy = 4.1;
//	cvData.convAvgVoltage = 1.2;
//	cvData.convAvgCurrent = 2.2;
//	cvData.convCurrPower = 3.2;
//	cvData.convEnergy = 4.2;
	cvData.avgCurrent = 1;
	cvData.avgVoltage = 2;
	cvData.currPower = 3;
	cvData.energy = 4;

	CreatePostString(&post, &gData, &cvData, &sData, deg);
	diag.SendDiagnostics(&response, &post);
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
