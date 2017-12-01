#ifndef _SYSTEM_STRUCTS_H_
#define _SYSTEM_STRUCTS_H_

#include<inttypes.h>

typedef struct SGPSData {
	bool gpsActive;

	// Time in GMT
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
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
//	float panelAvgVoltage;
//	float panelAvgCurrent;
//	float panelCurrPower;
//	float panelEnergy;
//	float battAvgVoltage;
//	float battAvgCurrent;
//	float battCurrPower;
//	float battEnergy;
//	float convAvgVoltage;
//	float convAvgCurrent;
//	float convCurrPower;
//	float convEnergy;
	float avgCurrent;
	float avgVoltage;
	float currPower;
	float energy;
} CurrVoltData;

typedef struct SLightSensorData {
	double voltTop;
	double voltBottom;
	double voltLeft;
	double voltRight;
} LightSensorData;

typedef struct SSpaData {
	double azimuth;			//horizontal degrees
	double elevation;		//vertical degrees
	double zenith;
	int sunrise;
	int sunset;
	int current_time;
	int julianDay;
} SpaData;

typedef enum EStatus {
	OK,
	GPS_PARSE_ERROR,
	MA_DEVICE_NOT_DETECTED,
	CV_PARSE_ERROR,
	DIAG_NO_WIFI_SHIELD,
	DIAG_CANT_CONNECT_SERVER,
    MOTRO_DGR_INVALID,
	MOTRO_MOVE_HORIZONTAL_ERROR,
	MOTRO_MOVE_VERTICAL_ERROR
} Status;

#endif /* _SYSTEM_STRUCTS_H_ */
