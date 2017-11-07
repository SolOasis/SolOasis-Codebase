#ifndef _COMM_MODULE_H_
#define _COMM_MODULE_H_

#include "SystemStructs.h"
#include "CommIntfc.h"

class CommModule : public CommIntfc {
  private:
    Status GPSDataParser(const char * in, GPSData * gData);
    Status MagnetometerDataParser(const char * in, int8_t deg);
  public:
    CommModule();
    ~CommModule();
    Status EnableGPS();
    Status DisableGPS();
    Status EnableMagnetometer();
    Status DisableMagnetometer();
    Status SendDiagnostics(Diagnostics * d);
    Status GetMagnetometerData(int8_t * deg);
    Status GetGPSData(GPSData * gData);
    Status GetLightSensorData(LightSensorData * lData);
    Status GetVoltageAndCurrentData(CurrVoltData * cvData);
    Status PrintLog(const char * message);
};

#endif /* _COMM_MODULE_H_ */
