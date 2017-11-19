/*
 * DiagnosticsModule.cpp
 *
 *  Created on: Nov 9, 2017
 *      Author: Chris
 */

#include "DiagnosticsModule.h"

DiagnosticsModule::DiagnosticsModule() {
	WiFi.setPins(8,7,4,2);
}

DiagnosticsModule::~DiagnosticsModule() {
}


