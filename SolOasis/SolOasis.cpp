#include "Globals.h"
#include "Ports.h"
#include "Schedule.h"


//Will not need these includes in final version
#include "CommIntfc.h"
#include "CommModule.h"
#include "ControlIntfc.h"
#include "ControlModule.h"
#include "PositioningModule.h"
#include "SystemStructs.h"
#include "SPACalculation.h"
#include "LightSensorModule.h"
///////////////////////////////////////////////

#ifdef DEBUG
#include "Debug.h"
#endif

#ifdef RUN_TESTS
#include "Test/Test.h"
#include "Test/CommModuleTest.h"
#include "Test/CurrVoltModuleTest.h"
#include "Test/DiagnosticsModuleTest.h"
#include "Test/GPSModuleTest.h"
#include "Test/LightSensorModuleTest.h"
#include "Test/MagAccModuleTest.h"
#endif

int counter = 0;
double deg = 0;
Debug debug;
CommModule mod;
PositioningModule pos;
GPSData gData;
CurrVoltData cvData;
LightSensorData lsData;
SpaData sData;
String post, response;

static Status CreatePostString(String * post, GPSData* gData,
		CurrVoltData* cvData, SpaData* sData, double deg) {
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

	*post+="POST "; *post+=PATH; *post+=" HTTP/1.1\r\nHost: "; *post+=SERVER; *post+="\r\nContent-Type: application/json\r\nContent-Length: "
			+ String(json.length()); *post+="\r\n\r\n"; *post+=json;

	return OK;
}

void setup() {
	SetupPorts();
	SystemSetup();

#ifdef RUN_TESTS
	Test * tests[]={
#ifdef TEST_GPS
			new GPSModuleTest(),
#endif
#ifdef TEST_MAGACC
			new MagAccModuleTest(),
#endif
#ifdef TEST_CV
			new CurrVoltModuleTest(),
#endif
#ifdef TEST_LIGHTSENSOR
			new LightSensorTest(),
#endif
#ifdef TEST_DIAGNOSTICS
			new DiagnosticsModuleTest(),
#endif
#ifdef TEST_COMM_MODULE
			new CommModuleTest(),
#endif
			new DummyTest()
	};

	int i;
	for(i=0; i<sizeof(tests)/sizeof(Test*); i++){
		tests[i]->RunTests();
		delete tests[i];
	}
#endif

	gData.hour = 16;
	gData.minute = 20;
	gData.second = 20;
	gData.day = 16;
	gData.month = 11;
	gData.year = 2017;
	gData.latitude = 40.443651;
	gData.longitude = -79.958767;

	pos.GetSPAData(&gData,&sData);

	mod.EnableGPS();
	mod.EnableMagnetometer();
	mod.EnableWiFi();
}

void loop() {
	//  Serial.print("Loop ");Serial.println(counter++);
	//Serial.write("Can you read this?");
	debug.print("DEBUG: loop "); debug.println(counter++);
	mod.GetVoltageAndCurrentData(&cvData);
	mod.GetLightSensorData(&lsData);
	mod.GetMagnetometerData(&deg);

	CreatePostString(&post, &gData, &cvData, &sData, deg);
	mod.SendDiagnostics(&response, &post);

	delay(1000);

}
