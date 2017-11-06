#ifndef _COMM_INTFC_H_
#define _COMM_INTFC_H_

#include<inttypes.h>
#include "SystemStructs.h"

class CommIntfc {
  public:
    virtual ~CommIntfc(){};
    virtual int SendDiagnostics(Diagnostics * d);
    virtual int GetMagnetometerData(int8_t * degree);
    virtual int GetGPSData(GPSData * gData);
    virtual int GetLightSensorData(LightSensorData * lData);
    virtual int GetVoltageAndCurrentData(CurrVoltData * cvData);
    virtual int PrintLog(const char * message);
};

#endif /* _COMM_INTFC_H_ */
