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
#define DEBUG_BAUD 115200
#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
  // Required for Serial on Zero based boards
  #define Serial SERIAL_PORT_USBVIRTUAL
#endif

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

#define CPU_HZ 48000000
#define TIMER_PRESCALER_DIV 1024
#define INTR_RATE 1		// interrupt frequency in Hz

// Single setup function to setup debug and other
// single instance items
static inline void SystemSetup(){
#ifdef DEBUG
	Serial.begin(DEBUG_BAUD);
	while(!Serial){;};
#endif
}

#endif /* _GLOBALS_H_ */
