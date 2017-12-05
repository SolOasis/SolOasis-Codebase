/*
 * DiagnosticsModule.cpp
 *
 *  Created on: Nov 9, 2017
 *      Author: Chris
 */

#include <time.h>
#include "DiagnosticsModule.h"

//**************************************************************************************
// ~Diagnostics Module Constructor~
//**************************************************************************************
DiagnosticsModule::DiagnosticsModule() {
	// Set hardcoded WiFi pins
	WiFi.setPins(8,7,4,2);
}
//**************************************************************************************


//**************************************************************************************
// ~Diagnostics Module Destructor~
//**************************************************************************************
DiagnosticsModule::~DiagnosticsModule() {
	DisableModule();
}
//**************************************************************************************


//**************************************************************************************
// ~Enable Diagnostics Module~
// Connect the module to WiFi, if it has not already been connected
//**************************************************************************************
Status DiagnosticsModule::EnableModule() {

	int status = WL_IDLE_STATUS;

	// Only attempt to reconnect if not connected already
	if(WiFi.status() != WL_CONNECTED){
		WiFi.maxLowPowerMode();

		// Check that WiFi chip is found (it had better be, its physically
		// connected to the MCU...)
		if(WiFi.status() == WL_NO_SHIELD){
#if defined(DEBUG) && defined(DEBUG_DIAG)
			debug.println("No WiFi shield, critical error occurred!");
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
		debug.println("\r\nConnected to WiFi!");
		debug.print("SSID:\t"); debug.println(SSID);
		IPAddress ip = WiFi.localIP();
		debug.print("IP:\t"); debug.print(ip[0]);
		debug.print('.'); debug.print(ip[1]);
		debug.print('.'); debug.print(ip[2]);
		debug.print('.'); debug.println(ip[3]);
		debug.print("RSSI:\t"); debug.print(WiFi.RSSI()); debug.println(" dBm");
#endif
	}
	return OK;
}
//**************************************************************************************


//**************************************************************************************
// ~Disable Diagnostics Module~
// Disconnect module from WiFi
//**************************************************************************************
Status DiagnosticsModule::DisableModule() {
	// need to put pin disable in
	WiFi.disconnect();
	return OK;
}
//**************************************************************************************


//**************************************************************************************
// ~Send Diagnostics Message~
// Send an HTTP request message and receive a response (generalized to
// allow for testing)
//**************************************************************************************
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

	client.stop();
	return OK;
}
//**************************************************************************************


//**************************************************************************************
// ~Get WiFi Time~
// Backup way to receive time if GPS module is not functioning
//**************************************************************************************
Status DiagnosticsModule::GetWiFiTime(StandardTime* t) {
	long int i = WiFi.getTime();
	struct tm * time = localtime(&i);
	t->hour = time->tm_hour;
	t->minute = time->tm_min;
	t->second = time->tm_sec;

	return OK;
}
//**************************************************************************************
