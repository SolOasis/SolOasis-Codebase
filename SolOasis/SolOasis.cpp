#include <Arduino.h>
#include "Globals.h"
#include "Ports.h"
#include "CommModule.h"
#include "SystemStructs.h"
#include "Debug.h"

int counter = 0;
double deg = 0;
Debug debug;
CommModule * mod;

GPSData gData;
CurrVoltData cvData;

void setup() {
//	while(!Serial);
//	Serial.begin(115200);
//	Serial1.begin(9600);
  SetupPorts();
  SystemSetup();
  mod = new CommModule();
  mod ->EnableGPS();
  mod ->EnableMagnetometer();
}

void loop() {
  debug.print("DEBUG: loop "); debug.println(counter++);
  mod->GetGPSData(&gData);
  mod->GetMagnetometerData(&deg);
  debug.print("Compass Degrees: "); debug.println(deg);
  mod->GetVoltageAndCurrentData(&cvData);
  delay(1000);

}

