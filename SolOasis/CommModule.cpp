
#include <stdlib.h>
#include "CommModule.h"

CommModule::CommModule(){
  
}

CommModule::~CommModule(){
  
}

Status CommModule::SendDiagnostics(Diagnostics * d){
  return OK;
}

Status CommModule::GetMagnetometerData(int8_t * degree){
  return OK;
}

Status CommModule::GetGPSData(GPSData * gData){
  return OK;
}

Status CommModule::GetLightSensorData(LightSensorData * lData){
  return OK;
}

Status CommModule::GetVoltageAndCurrentData(CurrVoltData * cvData){
  return OK;
}

Status CommModule::PrintLog(const char * message){
  return OK;
}

