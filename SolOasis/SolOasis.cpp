#include <Arduino.h>
#include "Globals.h"
#include "Ports.h"
#include "Schedule.h"


//Will not need these includes in final version
#include "CommIntfc.h"
#include "CommModule.h"
#include "ControlIntfc.h"
#include "ControlModule.h"
#include "PositioningIntfc.h"
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
CommModule * mod;
SPACalculation* spaCalculationPtr;
LightSensorModule* lightSensorModulePtr;

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

#endif
#ifdef TEST_DIAGNOSTICS

#endif
#ifdef TEST_COMM_MODULE

#endif
		  new DummyTest()
  };

  int i;
  for(i=0; i<sizeof(tests)/sizeof(Test*); i++){
	  tests[i]->RunTests();
	  delete tests[i];
  }
#endif

  mod = new CommModule();
  mod ->EnableGPS();
  spaCalculationPtr = new SPACalculation();
  lightSensorModulePtr = new LightSensorModule();
}

void loop() {
//  Serial.print("Loop ");Serial.println(counter++);
  //Serial.write("Can you read this?");
  debug.print("DEBUG: loop "); debug.println(counter++);
//  GPSData gData;
//  mod->GetGPSData(&gData);
//  gData.hour = 16;
//  gData.minute = 20;
//  gData.second = 20;
//  gData.day = 16;
//  gData.month = 11;
//  gData.year = 2017;
//  gData.latitude = 40.443651;
//  gData.longitude = -79.958767;
//  SpaData spaData;
//  spaCalculationPtr->GetSpaData(&gData, &spaData);
  LightSensorData lightSensorData;
  lightSensorModulePtr->GetLightSensorData(&lightSensorData);
  debug.print("Light sensor: "); 
//  debug.print(lightSensorData.voltTop); debug.print(" / "); 
//  debug.print(lightSensorData.voltRight);  debug.print(" / ");
//  debug.print(lightSensorData.voltBottom);  debug.print(" / ");
//  debug.println(lightSensorData.voltLeft);
  debug.print(analogRead(A2)); debug.print(" ");
  debug.print(analogRead(A3)); debug.print(" ");
  debug.print(analogRead(A4)); debug.print(" ");
  debug.println(analogRead(A5)); 
  debug.print(lightSensorData.voltTop - lightSensorData.voltBottom);  debug.print(" / ");
  debug.println(lightSensorData.voltRight - lightSensorData.voltLeft);

  
//  CommModule mod;
//  GPSData gData;
//  mod.EnableGPS();
//  mod.GetGPSData(&gData);
//mod.DisableGPS();
//  mod.EnableMagnetometer();
//  mod.GetMagnetometerData(&deg);
//  debug.print("Compass Degrees: "); debug.println(deg);

  delay(1000);

//	if (Serial.available()) {
//		char c = Serial.read();
//		GPSSerial.write(c);
//	}
//	if (GPSSerial.available()) {
//		char c = GPSSerial.read();
//		Serial.write(c);
//	}

}

