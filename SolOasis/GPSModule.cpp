
#include "GPSModule.h"

GPSModule::GPSModule(){
  GPS = Adafruit_GPS(&GPSSerial);
}

GPSModule::~GPSModule(){
  
}

Status GPSModule::EnableModule(){
  digitalWrite(GPSENPin, HIGH);
  GPS.begin(GPS_BAUD);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  
  return OK;
}

Status GPSModule::DisableModule(){
  digitalWrite(GPSENPin, LOW);
  return OK;
}

bool GPSModule::ModuleReady(){
  return GPS.fix;
}

Status GPSModule::GetGPSData(GPSData * gData){
  if(enabled){
    char c = GPS.read();
    while(!GPS.newNMEAreceived()){}
    if (!GPS.parse(GPS.lastNMEA())) return GPS_PARSEERROR;
    
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
  }
  else {
    gData->gpsActive = false;
  }

  return OK;
}

