#ifndef _GPS_MODULE_H_
#define _GPS_MODULE_H_


#include <Adafruit_GPS.h>
#include "Globals.h"
#include "Ports.h"
#include "SystemStructs.h"

#ifdef DEBUG
#include "Debug.h"
#endif

#define GPS_BAUD 9600

class GPSModule {
  private:
    static Adafruit_GPS GPS;
    static bool enabled;
#ifdef DEBUG
    Debug debug;
#endif
  public:
    GPSModule();
    ~GPSModule();
    Status EnableModule();
    Status DisableModule();
    bool ModuleReady();
    Status GetGPSData(GPSData * gData);
};

#endif /* _GPS_MODULE_H_ */
