/*
 * Globals.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <Arduino.h>
#include <HardwareSerial.h>

#define DEBUG

////////////////////////////////////////////////////////////////////////////////////////
// Different debug symbols for each module
////////////////////////////////////////////////////////////////////////////////////////
#ifdef DEBUG
//#define DEBUG_GPS
//#define DEBUG_CV
//#define DEBUG_MA
//#define DEBUG_LS
//#define DEBUG_SPA
//#define DEBUG_DIAG
#define DEBUG_SCHED
#define DEBUG_TEST
#endif
////////////////////////////////////////////////////////////////////////////////////////


#define DEBUG_BAUD 115200
#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
  // Required for Serial on Zero based boards
  #define Serial SERIAL_PORT_USBVIRTUAL
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Symbols for running tests (commented out if
// they aren't desired to be run)
////////////////////////////////////////////////////////////////////////////////////////
//#define RUN_TESTS
#define TEST_GPS
#define TEST_MAGACC
#define TEST_CV
#define TEST_COMM_MODULE
#define TEST_LIGHTSENSOR
#define TEST_DIAGNOSTICS
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// Redefine symbols for decimal, hex, and octal
// for the debug output
////////////////////////////////////////////////////////////////////////////////////////
#ifdef DEC
#undef DEC
#endif
#define DEC 10

#ifdef HEX
#undef HEX
#endif
#define HEX 16

#ifdef OCT
#undef OCT
#endif
#define OCT 8

#ifdef BIN
#undef BIN
#endif
#define BIN 2
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// ID strings for diagnostics server
////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
// Single setup function to setup debug and other
// single instance items
////////////////////////////////////////////////////////////////////////////////////////
static inline void SystemSetup(){
#ifdef DEBUG
	Serial.begin(DEBUG_BAUD);
	while(!Serial){;};
#endif
}
////////////////////////////////////////////////////////////////////////////////////////

#endif /* _GLOBALS_H_ */
