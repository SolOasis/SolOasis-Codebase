#ifndef _COMM_INTFC_H_
#define _COMM_INTFC_H_

#include<inttypes.h>

struct SProtocol {
  uint8_t version;      // version number
  uint8_t command;      // command enum val
  uint16_t length;      // payload length
  uint16_t checksum;    // payload checksum
  uint16_t padding;     // unused bytes
  uint8_t payload[40];  // 40 bytes of payload
};

struct SDiagnostics {
  uint8_t status;     // status enum value
  int8_t percentage;  // 0-100%
  int8_t efficiency;  // 0-100%
  double chargeRate;  // Watts per min
  double powerDraw;   // Watts per min
  double timeAlive;   // time system alive
};

typedef struct SProtocol Protocol;
typedef struct SDiagnostics Diagnostics;

class CommIntfc {
  private:
    
  public:
    int SendDiagnostics(Diagnostics * d);
    int GetMagnetometerData(int * x, int * y, int * z);
    int GetGPSData();
}

#endif /* _COMM_INTFC_H_ */
