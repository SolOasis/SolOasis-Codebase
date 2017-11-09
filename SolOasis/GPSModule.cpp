
#include "GPSModule.h"

GPSModule::GPSModule(){
	//Preset GPS off
	digitalWrite(GPSENPin, LOW);
	enabled = false;
}

GPSModule::~GPSModule(){
  
}

Status GPSModule::EnableModule(){
  digitalWrite(GPSENPin, HIGH);
  GPS.begin(GPS_BAUD);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  enabled = true;
  
#ifdef DEBUG
  debug.print("Send GPS Command: ");
  debug.println(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  debug.print("Send GPS Command: ");
  debug.println(PMTK_SET_NMEA_UPDATE_1HZ);
  debug.println("GPS Module Enabled!");
#endif
  return OK;
}

Status GPSModule::DisableModule(){
  digitalWrite(GPSENPin, LOW);
  enabled = false;
#ifdef DEBUG
  debug.println("GPS Module Disabled!");
#endif
  return OK;
}

bool GPSModule::ModuleReady(){
  return GPS.fix;
}

Status GPSModule::GetGPSData(GPSData * gData){
  if(enabled){
    char c = GPS.read();
#ifdef DEBUG
    debug.print("GPS read: "); debug.println(c);
#endif
    while(!GPS.newNMEAreceived()){}
    if (!GPS.parse(GPS.lastNMEA())){
#ifdef DEBUG
    	debug.println("GPS ERROR: Last NMEA sentence could not parse");
#endif
    	return GPS_PARSEERROR;
    }
    
    gData->hour = GPS.hour;
    gData->minute = GPS.minute;
    gData->seconds = GPS.seconds;
    gData->day = GPS.day;
    gData->month = GPS.month;
    gData->year = GPS.year;
  
    gData->latitude = GPS.latitude;
    gData->longitude = GPS.longitude;
    
    gData->gSpeed = GPS.speed;
    gData->trackAngle = GPS.angle;
    gData->altitude = GPS.altitude;
    gData->gpsActive = true;

#ifdef DEBUG
    debug.println("Outputting GPS Data...");
    debug.print("Hour:      "); debug.println(GPS.hour);
    debug.print("Minute:    "); debug.println(GPS.minute);
    debug.print("Seconds:   "); debug.println(GPS.seconds);
    debug.print("Day:       "); debug.println(GPS.day);
    debug.print("Month:     "); debug.println(GPS.month);
    debug.print("Year:      "); debug.println(GPS.year);
    debug.print("Latitude:  "); debug.println(GPS.latitude);
    debug.print("Longitude: "); debug.println(GPS.longitude);
    debug.print("Speed:     "); debug.println(GPS.speed);
    debug.print("Angle:     "); debug.println(GPS.angle);
    debug.print("Altitude:  "); debug.println(GPS.altitude);
#endif
  }
  else {
    gData->gpsActive = false;
#ifdef DEBUG
    debug.println("GPS not active!");
#endif
  }

  return OK;
}

