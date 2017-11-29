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

#ifdef DEBUG

//#define DEBUG_GPS
//#define DEBUG_CV
//#define DEBUG_MA
#define DEBUG_SPA
#define DEBUG_DIAG
#define DEBUG_SCHED
#define DEBUG_TEST

#endif


#define DEBUG_BAUD 115200
#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
  // Required for Serial on Zero based boards
  #define Serial SERIAL_PORT_USBVIRTUAL
#endif

#define RUN_TESTS
//#define TEST_GPS
#define TEST_MAGACC
#define TEST_CV
//#define TEST_COMM_MODULE
//#define TEST_LIGHTSENSOR
//#define TEST_DIAGNOSTICS

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

// Single setup function to setup debug and other
// single instance items
static inline void SystemSetup(){
#ifdef DEBUG
	Serial.begin(DEBUG_BAUD);
	while(!Serial){;};
#endif
}

#endif /* _GLOBALS_H_ */
