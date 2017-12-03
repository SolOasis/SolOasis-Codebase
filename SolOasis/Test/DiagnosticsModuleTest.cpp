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
	json+="\""; json+=GPS_ALT_ID; json+="\": "; json+=String(gData->altitude); json+=", ";

//	json+="\""; json+=CV_PAV_ID; json+="\": "; json+=String(cvData->panelAvgVoltage); json+=", ";
//	json+="\""; json+=CV_PAC_ID; json+="\": "; json+=String(cvData->panelAvgCurrent); json+=", ";
//	json+="\""; json+=CV_PCP_ID; json+="\": "; json+=String(cvData->panelCurrPower); json+=", ";
//	json+="\""; json+=CV_PE_ID; json+="\": "; json+=String(cvData->panelEnergy); json+=", ";
//	json+="\""; json+=CV_BAV_ID; json+="\": "; json+=String(cvData->battAvgVoltage); json+=", ";
//	json+="\""; json+=CV_BAC_ID; json+="\": "; json+=String(cvData->battAvgCurrent); json+=", ";
//	json+="\""; json+=CV_BCP_ID; json+="\": "; json+=String(cvData->battCurrPower); json+=", ";
//	json+="\""; json+=CV_BE_ID; json+="\": "; json+=String(cvData->battEnergy); json+=", ";
//	json+="\""; json+=CV_CAV_ID; json+="\": "; json+=String(cvData->convAvgVoltage); json+=", ";
//	json+="\""; json+=CV_CAC_ID; json+="\": "; json+=String(cvData->convAvgCurrent); json+=", ";
//	json+="\""; json+=CV_CCP_ID; json+="\": "; json+=String(cvData->convCurrPower); json+=", ";
//	json+="\""; json+=CV_CE_ID; json+="\": "; json+=String(cvData->convEnergy); json+=", ";

	json+="\""; json+=SPA_AZI_ID; json+="\": "; json+=String(sData->azimuth); json+=", ";
	json+="\""; json+=SPA_ELEV_ID; json+="\": "; json+=String(sData->elevation); json+=", ";
	json+="\""; json+=SPA_ZEN_ID; json+="\": "; json+=String(sData->zenith); json+=", ";
	json+="\""; json+=SPA_SRISE_ID; json+="\": "; json+=String(sData->sunrise.hour); json+=":";
	json+=String(sData->sunrise.minute); json+=":"; json+=String(sData->sunrise.second); json+=":"; json+=", ";
	json+="\""; json+=SPA_SSET_ID; json += "\": "; json+=String(sData->sunset.hour); json+=":";
	json+=String(sData->sunset.minute); json+=":"; json+=String(sData->sunset.second); json+=":"; json+=", ";
	json+="\""; json+=SPA_JUL_ID; json+="\": "; json+=String(sData->julianDay); json+=", ";

	json+="\""; json+=MA_DEG_ID; json+="\": "; json+=String(deg); json+=", ";

	int percent = 0;
//	if(cvData->battAvgVoltage > 12.7) percent = 100;
//	else if(cvData->battAvgVoltage > 12.4) percent = 75;
//	else if(cvData->battAvgVoltage > 12.2) percent = 50;
//	else if(cvData->battAvgVoltage > 12.0) percent = 25;

	json+="\""; json+=BATT_PERC_ID; json+="\": "; json+=String(percent); json+="%}}\r\n";

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
	sData.sunrise.hour = 0;
	sData.sunrise.minute = 0;
	sData.sunrise.second = 0;
	sData.sunset.hour = 23;
	sData.sunset.minute = 59;
	sData.sunset.second = 59;
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
