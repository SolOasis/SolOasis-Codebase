/*
 * Debug.cpp
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#include "Debug.h"

Debug::Debug(){
}

Debug::~Debug(){
}

size_t Debug::print(const char out[]) {
	return Serial.print(out);
}

size_t Debug::print(char out) {
	return Serial.print(out);
}

size_t Debug::print(unsigned char out, int format) {
	return Serial.print(out,format);
}

size_t Debug::print(int out, int format) {
	return Serial.print(out,format);
}

size_t Debug::print(unsigned int out, int format) {
	return Serial.print(out,format);
}

size_t Debug::print(long out, int format) {
	return Serial.print(out,format);
}

size_t Debug::print(unsigned long out, int format) {
	return Serial.print(out, format);
}

size_t Debug::print(double out, int format) {
	return Serial.print(out, format);
}

size_t Debug::println(const char out[]) {
	return Serial.println(out);
}

size_t Debug::println(char out) {
	return Serial.println(out);
}

size_t Debug::println(unsigned char out, int format) {
	return Serial.println(out, format);
}

size_t Debug::println(int out, int format) {
	return Serial.println(out, format);
}

size_t Debug::println(unsigned int out, int format) {
	return Serial.println(out, format);
}

size_t Debug::println(long out, int format) {
	return Serial.println(out, format);
}

size_t Debug::println(unsigned long out, int format) {
	return Serial.println(out, format);
}

size_t Debug::println(double out, int format) {
	return Serial.println(out, format);
}

size_t Debug::println(void) {
	return Serial.println();
}
