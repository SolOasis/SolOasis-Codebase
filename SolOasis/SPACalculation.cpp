


/*
 * SPACalculation.cpp
 *
 *  Created on: Nov 14, 2017
 *      Author: Allen
 */

#include "SPACalculation.h"
#include <Arduino.h>
#include "Timezone.h"
#include <TimeLib.h>
//#include <Time.h>


SPACalculation::SPACalculation(){
}

SPACalculation::~SPACalculation(){
}

Status SPACalculation::GetSpaData(const GPSData* gData, SpaData* sData){
	// Set now to UTC-0 Time
	setTime(gData->hour,
			gData->minute,
			gData->second,
			gData->day,
			gData->month,
			gData->year);
	// Calculate local time
	time_t eastern, utc;
	TimeChangeRule usEDT = {"EDT", Second, Sun, Mar, 2, -240};  //UTC - 4 hours
	TimeChangeRule usEST = {"EST", First, Sun, Nov, 2, -300};   //UTC - 5 hours
	Timezone usEastern(usEDT, usEST);
	utc = now();  //current time from the Time Library
	eastern = usEastern.toLocal(utc);
	// Set now to local time
	setTime(eastern);


	spa.year          = year();
	spa.month         = month();
	spa.day           = day();
	spa.hour          = hour();
	spa.minute        = minute();
	spa.second        = second();
	//spa.timezone      = TIMEZONE;
	spa.timezone      = (int)gData->longitude / 15;
	spa.delta_ut1     = DELTA_UT1;
	spa.delta_t       = DELTA_T;
	spa.longitude     = gData->longitude;
	spa.latitude      = gData->latitude;
	spa.elevation     = gData->altitude / 100;
	spa.pressure      = 1013.25;
	spa.temperature   = 15;
	spa.slope         = 0;
	spa.azm_rotation  = -10;
	spa.atmos_refract = 0.5667;
	spa.function      = SPA_ALL;

#if defined(DEBUG) && defined(DEBUG_SPA)
	debug.println("===SPA start===");
	//debug.println(now());
	//  debug.println(gData->hour);
	//  debug.println(gData->minute);
	//  debug.println(gData->second);
	//  debug.println(gData->day);
	//  debug.println(gData->month);
	//  debug.println(gData->year);
	debug.print(year());debug.print("-");debug.print(month());debug.print("-");debug.print(day());
	debug.print(" / ");debug.print(hour());debug.print(":");debug.println(minute());debug.print(":");debug.println(second());
	debug.print("GPS: ("); debug.print(spa.longitude); debug.print(", "); debug.print(spa.latitude); debug.println(")");
#endif

	//call the SPA calculate function and pass the SPA structure

	int result = spa_calculate(&spa);

	if (result == 0)  //check for SPA errors
	{
		//display the results inside the SPA structure

		sData->julianDay = spa.jd;
		sData->azimuth = spa.azimuth;
		sData->elevation = 90 - spa.zenith;
		sData->zenith = spa.zenith;
		sData->sunrise = spa.sunrise;
		sData->sunset = spa.sunset;
		//sData->time = spa.;
#if defined(DEBUG) && defined(DEBUG_SPA)

		debug.print("JulianDay:");
		debug.println(sData->julianDay);
		debug.print("Azimuth:");
		debug.println(sData->azimuth);
		debug.print("Elevation:");
		debug.println(sData->elevation);

		float mmin, sec; // For sunrise/set
		mmin = 60.0 * (spa.sunrise - (int)(spa.sunrise));
		sec = 60.0 * (mmin - (int)mmin);
		debug.print("Sunrise (Local Time):");
		debug.print((int)spa.sunrise); debug.print(":"); debug.print((int)mmin); debug.print(":"); debug.println((int)sec);

		mmin = 60.0 * (spa.sunset - (int)(spa.sunset));
		sec = 60.0 * (mmin - (int)mmin);
		debug.print("Sunset (Local Time):");
		debug.print((int)spa.sunset); debug.print(":"); debug.print((int)mmin); debug.print(":");	debug.println((int)sec);
#endif

	} else {
#if defined(DEBUG) && defined(DEBUG_SPA)
		debug.print("SPA Error Code: ");
		debug.println(result);
#endif

	}
#if defined(DEBUG) && defined(DEBUG_SPA)
	debug.println("===SPA end===");
#endif
	return(OK);


}


