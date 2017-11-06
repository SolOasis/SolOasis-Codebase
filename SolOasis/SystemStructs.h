#ifndef _SYSTEM_STRUCTS_H_
#define _SYSTEM_STRUCTS_H_

#include<inttypes.h>

typedef struct SProtocol {
  uint8_t ptclVersion;      // version number
  uint8_t command;      // command enum val
  uint16_t payloadLength;      // payload length
  uint16_t checksum;    // payload checksum
  uint16_t padding;     // unused bytes
  uint8_t payload[40];  // 40 bytes of payload
} Protocol;

typedef struct SDiagnostics {
  uint8_t sysStatus;     // status enum value
  int8_t percentage;  // 0-100%
  int8_t efficiency;  // 0-100%
  double chargeRate;  // Watts per min
  double powerDraw;   // Watts per min
  double timeAlive;   // time system alive
} Diagnostics;

typedef struct SGPSData {
  // Time in GMT
  int8_t hour;
  int8_t minutes;
  int8_t seconds;
  bool dataVoid;
  bool gpsActive;

  //latitude format: DDMM.MMMM
  int16_t latDeg;
  double latMin;
  bool north;         // north true (pos), south false (neg)

  //longitude format: DDDMM.MMMM
  int16_t longDeg;
  double longMin;
  bool east;          // east true (pos), west false (neg)
  
  double gSpeed;      //in knots
  double trackAngle;  //direction based on past travel
  int8_t day;
  int8_t month;
  int8_t year;
} GPSData;

typedef struct  SCurrVoltData {
  double panelVoltage;
  double panelCurrent;
  double battVoltage;
  double battCurrent;
  double convVoltage;
  double convCurrent;
} CurrVoltData;

typedef struct SLightSensorData {
  double voltTop;
  double voltBottom;
  double voltLeft;
  double voltRight;
} LightSensorData;

#endif /* _SYSTEM_STRUCTS_H_ */
