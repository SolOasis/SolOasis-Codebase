/*
 * DiagnosticsModule.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#ifndef _DIAGNOSTICS_MODULE_H_
#define _DIAGNOSTICS_MODULE_H_

#include <WiFi101.h>
#include "Globals.h"
#include "SystemStructs.h"
#include "Ports.h"

#ifdef DEBUG
#include "Debug.h"
#endif

#define SSID		"<wifi-ssid>"
#define PASSWORD	"<wifi-password>"
#define SERVER		"www.servername.com"
#define REQUEST		"TO-DO"

class DiagnosticsModule{
private:
#ifdef DEBUG
	Debug debug;
#endif

	WiFiClient client;

public:
	DiagnosticsModule();
	~DiagnosticsModule();
	Status EnableModule();
	Status DisableModule();
	Status SendDiagnostics(Diagnostics * dData);
};

#endif /* _DIAGNOSTICS_MODULE_H_ */
