/*
 * Debug.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include<inttypes.h>
#include<stdio.h>
#include<HardwareSerial.h>
#include "Globals.h"

//#define DEBUG_BAUD 115200

class Debug {
private:

public:
	Debug();
	~Debug();

//    size_t print(const __FlashStringHelper *);
//    size_t print(const String &);
    size_t print(const char out[]);
    size_t print(char out);
    size_t print(unsigned char out, int format = DEC);
    size_t print(int out, int format = DEC);
    size_t print(unsigned int out, int format = DEC);
    size_t print(long out, int format = DEC);
    size_t print(unsigned long out, int format = DEC);
    size_t print(double out, int format = BIN);
//    size_t print(const Printable&);

//    size_t println(const __FlashStringHelper *);
//    size_t println(const String &s);
    size_t println(const char out[]);
    size_t println(char out);
    size_t println(unsigned char out, int format = DEC);
    size_t println(int out, int format = DEC);
    size_t println(unsigned int out, int format = DEC);
    size_t println(long out, int format = DEC);
    size_t println(unsigned long out, int format = DEC);
    size_t println(double out, int format = BIN);
//    size_t println(const Printable&);
    size_t println(void);
};


#endif /* _DEBUG_H_ */
