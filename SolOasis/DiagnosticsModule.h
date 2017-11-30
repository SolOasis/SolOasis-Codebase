/*
 * DiagnosticsModule.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#ifndef _DIAGNOSTICS_MODULE_H_
#define _DIAGNOSTICS_MODULE_H_

#include <WiFi101.h>
#include <stdlib.h>
#include <string>
#include "Globals.h"
#include "SystemStructs.h"
#include "Ports.h"

#ifdef DEBUG
#include "Debug.h"
#endif

#define STATION_ID			"0"
#define SSID				"H2P"
#define PASSWORD			"1abc2bc3c4"
//#define SERVER			"https://desolate-depths-35197.herokuapp.com"
#define SERVER				"desolate-depths-35197.herokuapp.com"
//#define HOST				"desolate-depths-35197.herokuapp.com"
#define PATH				"/SolOasis/api/v1.0/update/"
#define PORT_HTTP			80
#define PORT_HTTPS			443
#define CONNECT_REQ			"GET / HTTP/1.1\nHost: desolate-depths-35197.herokuapp.com\nConnection: close\n"
#define WIFI_CONNECT_DELAY	10000
#define POST_ANSWER_DELAY	5000
#define BUFF_SIZE			4096

#define GPS_HOUR_ID			"Hour"
#define GPS_MIN_ID			"Minutes"
#define GPS_SEC_ID			"Seconds"
#define GPS_DAY_ID			"Day"
#define GPS_MONTH_ID		"Month"
#define GPS_YEAR_ID			"Year"
#define GPS_LAT_ID			"Latitude"
#define GPS_LONG_ID			"Longitude"
#define GPS_ALT_ID			"Altitude"

#define CV_PAV_ID			"PanelAvgVoltage"
#define CV_PAC_ID			"PanelAvgCurrent"
#define CV_PCP_ID			"PanelCurrPower"
#define CV_PE_ID			"PanelEnergy"
#define CV_BAV_ID			"BatteryAvgVoltage"
#define CV_BAC_ID			"BatteryAvgCurrent"
#define CV_BCP_ID			"BatteryCurrPower"
#define CV_BE_ID			"BatteryEnergy"
#define CV_CAV_ID			"ConverterAvgVoltage"
#define CV_CAC_ID			"ConverterAvgCurrent"
#define CV_CCP_ID			"ConverterCurrPower"
#define CV_CE_ID			"ConverterEnergy"

#define SPA_AZI_ID			"Azimuth"
#define SPA_ELEV_ID			"Elevation"
#define SPA_ZEN_ID			"Zenith"
#define SPA_SRISE_ID		"Sunrise"
#define SPA_SSET_ID			"Sunset"
#define SPA_JUL_ID			"JulianDay"

#define MA_DEG_ID			"CompassDegrees"

#define BATT_PERC_ID		"BatteryPercentage"

class DiagnosticsModule{
private:
#ifdef DEBUG
	Debug debug;
#endif

	WiFiSSLClient client;
	Status CreatePostString(String * post, GPSData * gData, CurrVoltData * cvData, SpaData * sData, double deg);
public:
	DiagnosticsModule();
	~DiagnosticsModule();
	Status EnableModule();
	Status DisableModule();
	Status SendDiagnostics(GPSData * gData, CurrVoltData * cvData, SpaData * sData, double deg);
};

#endif /* _DIAGNOSTICS_MODULE_H_ */
