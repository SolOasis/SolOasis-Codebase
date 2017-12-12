#include "Globals.h"
#include "Ports.h"
#include "Schedule.h"

#ifdef RUN_TESTS
#include "Test/Test.h"
#include "Test/CurrVoltModuleTest.h"
#include "Test/DiagnosticsModuleTest.h"
#include "Test/GPSModuleTest.h"
#include "Test/LightSensorModuleTest.h"
#include "Test/MagAccModuleTest.h"
#endif

Schedule s;

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
			new LightSensorModuleTest(),
#endif
#ifdef TEST_DIAGNOSTICS
			new DiagnosticsModuleTest(),
#endif
			new DummyTest()
	};

	int i;
	for(i=0; i<sizeof(tests)/sizeof(Test*); i++){
		tests[i]->RunTests();
		delete tests[i];
	}
#endif

	s.InitSchedule();
}


void loop() {
	s.RunSchedule();
}
