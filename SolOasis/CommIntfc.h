#ifndef _COMM_INTFC_H_
#define _COMM_INTFC_H_

#include<inttypes.h>
#include "SystemStructs.h"

class CommIntfc {
  public:
    virtual ~CommIntfc(){};
    virtual Status EnableGPS();
    virtual Status DisableGPS();
    virtual Status EnableMagnetometer();
    virtual Status DisableMagnetometer();
    virtual Status SendDiagnostics(Diagnostics * d);
    virtual Status GetMagnetometerData(int8_t * deg);
    virtual Status GetGPSData(GPSData * gData);
    virtual Status GetLightSensorData(LightSensorData * lData);
    virtual Status GetVoltageAndCurrentData(CurrVoltData * cvData);
    virtual Status PrintLog(const char * message);
};

#endif /* _COMM_INTFC_H_ */
