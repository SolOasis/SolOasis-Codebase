#include <Arduino.h>
#include "Globals.h"
#include "Ports.h"
#include "CommModule.h"
#include "SystemStructs.h"
#include "Debug.h"

int counter = 0;
double deg = 0;
Debug debug;
void setup() {
  //Serial.begin(115200);
  SetupPorts();
  SystemSetup();
}

void loop() {
//  Serial.print("Loop ");Serial.println(counter++);
  //Serial.write("Can you read this?");
  debug.print("DEBUG: loop "); debug.println(counter++);
  CommModule mod;
//  GPSData gData;
//  mod.EnableGPS();
//  mod.GetGPSData(&gData);
//  mod.DisableGPS();
  mod.EnableMagnetometer();
  mod.GetMagnetometerData(&deg);
  debug.print("Compass Degrees: "); debug.println(deg);

  delay(1000);
}

