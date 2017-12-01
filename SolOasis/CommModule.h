#ifndef _COMM_MODULE_H_
#define _COMM_MODULE_H_

#include "Globals.h"
#include "SystemStructs.h"
#include "CommIntfc.h"
#include "GPSModule.h"
#include "MagAccModule.h"
#include "CurrVoltModule.h"
#include "DiagnosticsModule.h"
#include "LightSensorModule.h"

#ifdef DEBUG
#include "Debug.h"
#endif

class CommModule : public CommIntfc {
  private:

	// Module objects for communications
	// module to use
	GPSModule gps;
	MagAccModule mag;
	CurrVoltModule cv;
	LightSensorModule ls;
	DiagnosticsModule diagnostics;

#ifdef DEBUG
	Debug debug;
#endif

  public:
    CommModule();
    ~CommModule();
    Status EnableGPS();
    Status DisableGPS();
    Status EnableMagnetometer();
    Status DisableMagnetometer();
    Status EnableWiFi();
    Status DisableWiFi();
    Status SendDiagnostics(String * response, String * request);
    Status GetMagnetometerData(double * deg);
    Status GetGPSData(GPSData * gData);
    Status GetLightSensorData(LightSensorData * lsData);
    Status GetVoltageAndCurrentData(CurrVoltData * cvData);
};

#endif /* _COMM_MODULE_H_ */
