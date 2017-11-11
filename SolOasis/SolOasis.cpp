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
void setup() {
//	while(!Serial);
//	Serial.begin(115200);
//	Serial1.begin(9600);
  SetupPorts();
  SystemSetup();
  mod = new CommModule();
  mod ->EnableGPS();
}

void loop() {
//  Serial.print("Loop ");Serial.println(counter++);
  //Serial.write("Can you read this?");
  debug.print("DEBUG: loop "); debug.println(counter++);
  GPSData gData;
  mod->GetGPSData(&gData);
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

