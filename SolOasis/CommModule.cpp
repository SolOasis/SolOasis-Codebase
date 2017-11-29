#include "CommModule.h"

CommModule::CommModule(){

}

CommModule::~CommModule(){

}

Status CommModule::SendDiagnostics(GPSData * gData, CurrVoltData * cvData, SpaData * sData, double deg){
	return diagnostics.SendDiagnostics(gData,cvData,sData,deg);
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
	cv.RecieveData(cvData);
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

Status CommModule::EnableWiFi() {
	return diagnostics.EnableModule();
}

Status CommModule::DisableWiFi() {
	return diagnostics.DisableModule();
}

Status CommModule::PrintLog(const char * message){
	return OK;
}



