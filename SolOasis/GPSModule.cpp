
#include "GPSModule.h"

GPSModule::GPSModule(){
	//Preset GPS off
	digitalWrite(GPSENPin, LOW);
	enabled = false;
}

GPSModule::~GPSModule(){
  
}

//SIGNAL(TIMER0_COMPA_vect){
//	char c = GPS.read();
//#ifdef DEBUG
//    debug.print("GPS read: "); debug.println(c);
//#endif
//}
//
//GPSModule::enableInterrupt(bool en){
//	if (en) {
//	    // Timer0 is already used for millis() - we'll just interrupt somewhere
//	    // in the middle and call the "Compare A" function above
//	    OCR0A = 0xAF;
//	    TIMSK0 |= _BV(OCIE0A);
//	    usingInterrupt = true;
//	  } else {
//	    // do not call the interrupt function COMPA anymore
//	    TIMSK0 &= ~_BV(OCIE0A);
//	    usingInterrupt = false;
//	  }
//}

Status GPSModule::EnableModule(){
  digitalWrite(GPSENPin, HIGH);
  GPS.begin(GPS_BAUD);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPSSerial.println(PMTK_Q_RELEASE);
  
#ifdef DEBUG
  debug.print("Send GPS Command: ");
  debug.println(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  debug.print("Send GPS Command: ");
  debug.println(PMTK_SET_NMEA_UPDATE_1HZ);
#endif


#ifdef DEBUG
  debug.println("GPS Module Enabled!");
#endif
  enabled = true;
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

Status GPSModule::GetFix(){

}

Status GPSModule::GetGPSData(GPSData * gData){
  if(enabled){
//    char c = GPS.read();
//#ifdef DEBUG
//    debug.print("GPS read: "); debug.println(c);
//#endif
	while(GPSSerial.available()){
		char c = GPS.read();
#ifdef DEBUG
		debug.print("GPS read: "); debug.print(c);
#endif
		if(GPS.newNMEAreceived()) break;
	};
    //while(!GPS.newNMEAreceived()){}
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

