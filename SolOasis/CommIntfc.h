#ifndef _COMM_INTFC_H_
#define _COMM_INTFC_H_

#include "SystemStructs.h"

class CommIntfc {
  public:
    virtual ~CommIntfc(){};
    virtual Status EnableGPS() = 0;
    virtual Status DisableGPS() = 0;
    virtual Status EnableMagnetometer() = 0;
    virtual Status DisableMagnetometer() = 0;
    virtual Status EnableWiFi() = 0;
    virtual Status DisableWiFi() = 0;
    virtual Status SendDiagnostics(String * response, String * request) = 0;
    virtual Status GetMagnetometerData(double * deg) = 0;
    virtual Status GetGPSData(GPSData * gData) = 0;
    virtual Status GetLightSensorData(LightSensorData * lsData) = 0;
    virtual Status GetVoltageAndCurrentData(CurrVoltData * cvData) = 0;
    virtual Status PrintLog(const char * message) = 0;
};

#endif /* _COMM_INTFC_H_ */
