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
	bool gpsActive;

	// Time in GMT
	uint8_t hour;
	uint8_t minute;
	uint8_t seconds;
	uint8_t day;
	uint8_t month;
	uint8_t year;

	bool fix;
	uint8_t fixQuality;

	//latitude format: DDMM.MMMM
	double latitude;
	//longitude format DDDMM.MMMM
	double longitude;

	double gSpeed;      //in knots
	double trackAngle;  //direction based on past travel
	double altitude;

} GPSData;

typedef struct SCurrVoltData {
	float panelVoltage;
	float panelCurrent;
	float panelPower;
	float battVoltage;
	float battCurrent;
	float battPower;
	float convVoltage;
	float convCurrent;
	float convPower;
} CurrVoltData;

typedef struct SLightSensorData {
	double voltTop;
	double voltBottom;
	double voltLeft;
	double voltRight;
} LightSensorData;

typedef enum EStatus {
	OK, GPS_PARSEERROR, GPS_LOCUSERROR, MA_DEVICENOTDETECTED, CV_PARSEERROR
} Status;

#endif /* _SYSTEM_STRUCTS_H_ */
