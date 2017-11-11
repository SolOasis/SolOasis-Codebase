#ifndef _GPS_MODULE_H_
#define _GPS_MODULE_H_


#include <Adafruit_GPS.h>
#include "Globals.h"
#include "Ports.h"
#include "SystemStructs.h"

#ifdef DEBUG
#include "Debug.h"
#endif

class GPSModule {
  private:
    Adafruit_GPS GPS = Adafruit_GPS(&GPSSerial);
    bool enabled;

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
