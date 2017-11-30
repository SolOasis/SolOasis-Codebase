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
#include "Globals.h"
#include "SystemStructs.h"
#include "Ports.h"

#ifdef DEBUG
#include "Debug.h"
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Diagnostics constants
////////////////////////////////////////////////////////////////////////////////////////
#define STATION_ID			"0"
#define SSID				"H2P"
#define PASSWORD			"1abc2bc3c4"
#define SERVER				"desolate-depths-35197.herokuapp.com"
#define PATH				"/SolOasis/api/v1.0/update/"
#define PORT_HTTP			80
#define PORT_HTTPS			443
#define CONNECT_REQ			"GET / HTTP/1.1\nHost: desolate-depths-35197.herokuapp.com\nConnection: close\n"
#define WIFI_CONNECT_DELAY	10000
#define POST_ANSWER_DELAY	5000
#define BUFF_SIZE			4096
////////////////////////////////////////////////////////////////////////////////////////

class DiagnosticsModule{
private:
#ifdef DEBUG
	Debug debug;
#endif
	WiFiSSLClient client;
public:
	DiagnosticsModule();
	~DiagnosticsModule();
	Status EnableModule();
	Status DisableModule();
	Status SendDiagnostics(String * response, String * request);
};

#endif /* _DIAGNOSTICS_MODULE_H_ */
