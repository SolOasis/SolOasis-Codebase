#include "CommModule.h"

CommModule::CommModule(){
  
}

CommModule::~CommModule(){
  
}

Status CommModule::SendDiagnostics(Diagnostics * d){
  return OK;
}

Status CommModule::GetMagnetometerData(double * deg){
  return mag.GetMagData(deg);
}

Status CommModule::GetGPSData(GPSData * gData){
  return gps.GetGPSData(gData);
}

Status CommModule::GetLightSensorData(LightSensorData * lData){
  return OK;
}

Status CommModule::GetVoltageAndCurrentData(CurrVoltData * cvData){
  return OK;
}

Status CommModule::EnableGPS() {
	return gps.EnableModule();
}

Status CommModule::DisableGPS() {
	return gps.DisableModule();
}

Status CommModule::EnableMagnetometer() {
	return mag.EnableModule();
}

Status CommModule::DisableMagnetometer() {
	return mag.DisableModule();
}

Status CommModule::PrintLog(const char * message){
  return OK;
}



