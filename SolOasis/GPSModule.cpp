#include <inttypes.h>
#include "GPSModule.h"


GPSModule::GPSModule() {
	//Preset GPS off
	digitalWrite(GPSENPin, LOW);
	enabled = false;
}

GPSModule::~GPSModule() {

}

Status GPSModule::EnableModule() {
	digitalWrite(GPSENPin, HIGH);
	GPS.begin(GPS_BAUD);
	GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
	GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
	GPSSerial.println(PMTK_Q_RELEASE);

#if defined(DEBUG) && defined(DEBUG_GPS)
	debug.print("Send GPS Command: "); debug.println(PMTK_SET_NMEA_OUTPUT_RMCGGA);
	debug.print("Send GPS Command: "); debug.println(PMTK_SET_NMEA_UPDATE_1HZ);
#endif

#if defined(DEBUG) && defined(DEBUG_GPS)
	debug.println("GPS Module Enabled!");
#endif
	enabled = true;
	return OK;
}

Status GPSModule::DisableModule() {
	digitalWrite(GPSENPin, LOW);
	enabled = false;
#if defined(DEBUG) && defined(DEBUG_GPS)
	debug.println("GPS Module Disabled!");
#endif
	return OK;
}

bool GPSModule::ModuleReady() {
	return GPS.fix;
}

Status GPSModule::GetGPSData(GPSData * gData) {
	if (enabled) {
#if defined(DEBUG) && defined(DEBUG_GPS)
			debug.print("GPS read: ");
#endif
		while (GPSSerial.available()) {
			char c = GPS.read();
#if defined(DEBUG) && defined(DEBUG_GPS)
			debug.print(c);
#endif
			if (GPS.newNMEAreceived())
				break;
		};
		if (!GPS.parse(GPS.lastNMEA())) {
#if defined(DEBUG) && defined(DEBUG_GPS)
			debug.println("GPS ERROR: Last NMEA sentence could not parse");
#endif
			return GPS_PARSE_ERROR;
		}

		gData->hour = GPS.hour;
		gData->minute = GPS.minute;
		gData->second = GPS.seconds;
		gData->day = GPS.day;
		gData->month = GPS.month;
		gData->year = GPS.year;

		gData->fix = GPS.fix;
		gData->fixQuality = GPS.fixquality;

		gData->latitude = GPS.latitudeDegrees;
		gData->longitude = GPS.longitudeDegrees;

		gData->gSpeed = GPS.speed;
		gData->trackAngle = GPS.angle;
		gData->altitude = GPS.altitude;
		gData->gpsActive = true;

#if defined(DEBUG) && defined(DEBUG_GPS)
		debug.println("Outputting GPS Data...");
		debug.print("Fix:         "); debug.println(GPS.fix);
		debug.print("Fix Quality: "); debug.println(GPS.fixquality);
		debug.print("Hour:        "); debug.println(GPS.hour);
		debug.print("Minute:      "); debug.println(GPS.minute);
		debug.print("Seconds:     "); debug.println(GPS.seconds);
		debug.print("Day:         "); debug.println(GPS.day);
		debug.print("Month:       "); debug.println(GPS.month);
		debug.print("Year:        "); debug.println(gData->year);
		debug.print("Latitude:    "); debug.println(gData->latitude);
		debug.print("Longitude:   "); debug.println(gData->longitude);
		debug.print("Speed:       "); debug.println(GPS.speed);
		debug.print("Angle:       "); debug.println(GPS.angle);
		debug.print("Altitude:    "); debug.println(GPS.altitude);
#endif
	} else {
		gData->gpsActive = false;
#if defined(DEBUG) && defined(DEBUG_GPS)
		debug.println("GPS not active!");
#endif
	}

	return OK;
}


