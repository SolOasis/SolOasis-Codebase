#ifndef _COMM_MODULE_H_
#define _COMM_MODULE_H_

#include "SystemStructs.h"
#include "CommIntfc.h"

class CommModule : public CommIntfc {
  private:

  public:
    CommModule();
    ~CommModule();
    int SendDiagnostics(Diagnostics * d);
    int GetMagnetometerData(int8_t * degree);
    int GetGPSData(GPSData * gData);
    int GetLightSensorData(LightSensorData * lData);
    int GetVoltageAndCurrentData(CurrVoltData * cvData);
    int PrintLog(const char * message);
};

#endif /* _COMM_MODULE_H_ */
