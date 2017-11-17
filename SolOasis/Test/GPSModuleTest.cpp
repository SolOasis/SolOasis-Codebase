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
#if defined(DEBUG) && defined(DEBUG_TEST)
	debug.print("GPS read data test ");debug.println((result==PASS)?"passed!":"failed!");
#endif
}

TestStatus GPSModuleTest::GPSReadDataTest() {
#if defined(DEBUG) && defined(DEBUG_TEST)
	debug.println("*** GPS READ DATA TEST ***");
	debug.println("Note that it takes a long time for GPS data to get a fix.");
	debug.print("Waiting for fix.");
#endif
	while(!gData.fix){
		gps.GetGPSData(&gData);
		delay(DELAY_30SEC);
#if defined(DEBUG) && defined(DEBUG_TEST)
		debug.print('.');
#endif
	}

#if defined(DEBUG) && defined(DEBUG_TEST)
	debug.println("\r\nGPS fix found!");
	debug.println("\r\n3 sets of GPS data:");
#endif

	int sets = 0;
	Status s;
	while(sets < NUM_RUNS){
		s = gps.GetGPSData(&gData);
		if(s == OK){
			sets++;
#if defined(DEBUG) && defined(DEBUG_TEST)
			debug.print("Test data set #"); debug.println(sets);
			debug.print("Fix:         "); debug.println(gData.fix);
			debug.print("Fix Quality: "); debug.println(gData.fixQuality);
			debug.print("Hour:        "); debug.println(gData.hour);
			debug.print("Minute:      "); debug.println(gData.minute);
			debug.print("Seconds:     "); debug.println(gData.second);
			debug.print("Day:         "); debug.println(gData.day);
			debug.print("Month:       "); debug.println(gData.month);
			debug.print("Year:        "); debug.println(gData.year);
			debug.print("Latitude:    "); debug.println(gData.latitude);
			debug.print("Longitude:   "); debug.println(gData.longitude);
			debug.print("Speed:       "); debug.println(gData.gSpeed);
			debug.print("Angle:       "); debug.println(gData.trackAngle);
			debug.print("Altitude:    "); debug.println(gData.altitude);
#endif
		}
	}

	return PASS;
}
