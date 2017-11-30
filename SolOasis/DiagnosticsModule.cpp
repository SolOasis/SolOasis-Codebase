/*
 * DiagnosticsModule.cpp
 *
 *  Created on: Nov 9, 2017
 *      Author: Chris
 */

#include "DiagnosticsModule.h"

DiagnosticsModule::DiagnosticsModule() {
	// Set hardcoded WiFi pins
	WiFi.setPins(8,7,4,2);
}

DiagnosticsModule::~DiagnosticsModule() {
	DisableModule();
}

Status DiagnosticsModule::EnableModule() {
	WiFi.noLowPowerMode();
	int status = WL_IDLE_STATUS;
	if(WiFi.status() == WL_NO_SHIELD){
#if defined(DEBUG) && defined(DEBUG_DIAG)

#endif
		return DIAG_NO_WIFI_SHIELD;
	}

#if defined(DEBUG) && defined(DEBUG_DIAG)
	debug.print("Connecting to WiFi...");
#endif
	while(status!=WL_CONNECTED){
		status = WiFi.begin(SSID,PASSWORD);
		delay(WIFI_CONNECT_DELAY);
#if defined(DEBUG) && defined(DEBUG_DIAG)
		debug.print('.');
#endif
	}
#if defined(DEBUG) && defined(DEBUG_DIAG)
	debug.println("\nConnected to WiFi!");
	debug.print("SSID:\t"); debug.println(SSID);
	IPAddress ip = WiFi.localIP();
	debug.print("IP:\t"); debug.print(ip[0]);
	debug.print('.'); debug.print(ip[1]);
	debug.print('.'); debug.print(ip[2]);
	debug.print('.'); debug.println(ip[3]);
	debug.print("RSSI:\t"); debug.print(WiFi.RSSI()); debug.println(" dBm");
#endif

	return OK;
}

Status DiagnosticsModule::DisableModule() {
	client.stop();
	WiFi.lowPowerMode();
	// need to put pin disable in
	return OK;
}

Status DiagnosticsModule::SendDiagnostics(String * response, String * request) {
	Status s = OK;
	int loc = 0;

	if(client.connect(SERVER,PORT_HTTPS)){
#if defined(DEBUG) && defined(DEBUG_DIAG)
		debug.println("Connected to server!");
#endif
	}
	else{
#if defined(DEBUG) && defined(DEBUG_DIAG)
		debug.println("Client failed to connect to server!");
#endif
		return DIAG_CANT_CONNECT_SERVER;
	}


	client.println(request->c_str());
	delay(POST_ANSWER_DELAY);
	while(client.available() && loc < BUFF_SIZE){
		*response = client.readString();
	}

#if defined(DEBUG) && defined(DEBUG_DIAG)
	debug.print("Read buffer: "); debug.println(response->c_str());
#endif

	return OK;
}
