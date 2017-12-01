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
ControlModule ctrl;
PositioningModule pos;
GPSData gData;
CurrVoltData cvData;
LightSensorData lsData;
SpaData sData;

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

//	mod.EnableGPS();
//	mod.EnableMagnetometer();
//	mod.EnableWiFi();
}
int hor = 0; int ver = 0;
void loop() {
	//  Serial.print("Loop ");Serial.println(counter++);
	//Serial.write("Can you read this?");
	debug.print("DEBUG: loop "); debug.println(counter++);
//	mod.GetVoltageAndCurrentData(&cvData);
//	mod.GetLightSensorData(&lsData);
//	mod.GetMagnetometerData(&deg);
//
//	mod.SendDiagnostics(&gData, &cvData, &sData, deg);

	hor += 15;
	ver += 15;
	if (hor > 180) hor = 0;
	if (ver > 180) ver = 0;
	//debug.println(ctrl.rotateMotors((int)hor, (int)ver));
	debug.print(hor); debug.print(", "); debug.println(ver);

	//delay(10);

}
