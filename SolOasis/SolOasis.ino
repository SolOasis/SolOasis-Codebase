#include <Arduino.h>
#include "Globals.h"
#include "Ports.h"
#include "CommModule.h"
#include "SystemStructs.h"
#include "Debug.h"
#include "SPACalculation.h"

int counter = 0;
double deg = 0;
Debug debug;
CommModule * mod;
SPACalculation* spaCalculationPtr;
void setup() {
//	while(!Serial);
//	Serial.begin(115200);
//	Serial1.begin(9600);
  SetupPorts();
  SystemSetup();
  mod = new CommModule();
  mod ->EnableGPS();
  spaCalculationPtr = new SPACalculation();
}

void loop() {
//  Serial.print("Loop ");Serial.println(counter++);
  //Serial.write("Can you read this?");
  debug.print("DEBUG: loop "); debug.println(counter++);
  GPSData gData;
  mod->GetGPSData(&gData);
  gData.hour = 16;
  gData.minute = 20;
  gData.second = 20;
  gData.day = 16;
  gData.month = 11;
  gData.year = 2017;
  gData.latitude = 40.443651;
  gData.longitude = -79.958767;
  SpaData spaData;
  spaCalculationPtr->GetSpaData(&gData, &spaData);
//  CommModule mod;
//  GPSData gData;
//  mod.EnableGPS();
//  mod.GetGPSData(&gData);
//mod.DisableGPS();
//  mod.EnableMagnetometer();
//  mod.GetMagnetometerData(&deg);
//  debug.print("Compass Degrees: "); debug.println(deg);

  delay(3000);

//	if (Serial.available()) {
//		char c = Serial.read();
//		GPSSerial.write(c);
//	}
//	if (GPSSerial.available()) {
//		char c = GPSSerial.read();
//		Serial.write(c);
//	}

}

