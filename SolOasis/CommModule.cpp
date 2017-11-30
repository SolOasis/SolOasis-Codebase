#include "CommModule.h"

CommModule::CommModule(){

}

CommModule::~CommModule(){

}

Status CommModule::SendDiagnostics(String * response, String * request){
	return diagnostics.SendDiagnostics(response, request);
}

Status CommModule::GetMagnetometerData(double * deg){
	return mag.GetMagData(deg);
}

Status CommModule::GetGPSData(GPSData * gData){
	return gps.GetGPSData(gData);
}

Status CommModule::GetLightSensorData(LightSensorData * lsData){
	return ls.GetLightSensorData(lsData);
}

Status CommModule::GetVoltageAndCurrentData(CurrVoltData * cvData){
	return cv.RecieveData(cvData);
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

Status CommModule::EnableWiFi() {
	return diagnostics.EnableModule();
}

Status CommModule::DisableWiFi() {
	return diagnostics.DisableModule();
}

Status CommModule::PrintLog(const char * message){
	return OK;
}



