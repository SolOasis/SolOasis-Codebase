/*
 * GPSModuleTest.cpp
 *
 *  Created on: Nov 16, 2017
 *      Author: Chris
 */

#include "GPSModuleTest.h"

GPSModuleTest::GPSModuleTest() {
	memset(&gData,0,sizeof(GPSData));
	gps.EnableModule();
}

GPSModuleTest::~GPSModuleTest() {
}

void GPSModuleTest::RunTests() {
	bool result;

	result = GPSReadDataTest();
	debug.print("GPS read data test ");debug.println((result==PASS)?"passed!":"failed!");
}

TestStatus GPSModuleTest::GPSReadDataTest() {
	debug.println("*** GPS READ DATA TEST ***");
	debug.println("Note that it takes a long time for GPS data to get a fix.");
	debug.println("This test will delay for 30 min to allow GPS to get fix.");

	int minToGo = 30;
	debug.print(minToGo); debug.println(" Minutes to go...");
	while(minToGo > 0){
		delay(DELAY_MINUTE);
		minToGo--;
		debug.print(minToGo); debug.println(" Minutes to go...");
	}
	debug.println("GPS warmed up!");
	debug.println("\r\n3 sets of GPS data:");
	int sets = 0;
	Status s;
	while(sets < 3){
		s = gps.GetGPSData(&gData);
		if(s == OK){
			sets++;
			debug.print("Test data set #"); debug.println(sets);
			debug.print("Fix:         "); debug.println(gData.fix);
			debug.print("Fix Quality: "); debug.println(gData.fixQuality);
			debug.print("Hour:        "); debug.println(gData.hour);
			debug.print("Minute:      "); debug.println(gData.minute);
			debug.print("Seconds:     "); debug.println(gData.seconds);
			debug.print("Day:         "); debug.println(gData.day);
			debug.print("Month:       "); debug.println(gData.month);
			debug.print("Year:        "); debug.println(gData.year);
			debug.print("Latitude:    "); debug.println(gData.latitude);
			debug.print("Longitude:   "); debug.println(gData.longitude);
			debug.print("Speed:       "); debug.println(gData.gSpeed);
			debug.print("Angle:       "); debug.println(gData.trackAngle);
			debug.print("Altitude:    "); debug.println(gData.altitude);
		}
	}

	return PASS;
}
