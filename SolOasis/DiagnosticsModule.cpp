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
#endif

	if(client.connect(SERVER,PORT)){
#if defined(DEBUG) && defined(DEBUG_DIAG)
		debug.println("Connected to server!");
#endif
	}

	return OK;
}

Status DiagnosticsModule::DisableModule() {
	client.stop();
	// need to put pin disable in
	return OK;
}

Status DiagnosticsModule::SendDiagnostics(GPSData* gData, CurrVoltData* cvData,
		SpaData* sData, double deg) {
	Status s = OK;
	char buffer[BUFF_SIZE];
	int loc = 0;
	String post = String("");

	if((s=CreatePostString(&post,gData,cvData,sData,deg)) != OK) return s;

	client.println(post.c_str());
	delay(POST_ANSWER_DELAY);
	while(client.available() && loc < BUFF_SIZE){
		buffer[loc++]=client.read();
	}

#if defined(DEBUG) && defined(DEBUG_DIAG)
	debug.print("Read buffer: "); debug.println(buffer);
#endif
	return OK;
}

Status DiagnosticsModule::CreatePostString(String * post, GPSData* gData,
		CurrVoltData* cvData, SpaData* sData, double deg) {
	String json = String("");
	json +="{\"ID\": "; json+=STATION_ID; json+=", ";
	json+="\""; json+=GPS_HOUR_ID; json+="\": "; json+=String((int)gData->hour); json+=", ";
	json+="\""; json+=GPS_MIN_ID; json+="\": "; json+=String((int)gData->minute); json+=", ";
	json+="\""; json+=GPS_SEC_ID; json+="\": "; json+=String((int)gData->second); json+=", ";
	json+="\""; json+=GPS_DAY_ID; json+="\": "; json+=String((int)gData->day); json+=", ";
	json+="\""; json+=GPS_MONTH_ID; json+="\": "; json+=String((int)gData->month); json+=", ";
	json+="\""; json+=GPS_YEAR_ID; json+="\": "; json+=String((int)gData->year); json+=", ";
	json+="\""; json+=GPS_LAT_ID; json+="\": "; json+=String(gData->latitude); json+=", ";
	json+="\""; json+=GPS_LONG_ID; json+="\": "; json+=String(gData->longitude); json+=", ";
	json+="\""; json+=GPS_ALT_ID; json+="\": "; json+=String(gData->altitude); json+="}\n";

	*post+="POST "; *post+=PATH; *post+=" HTTP/1.1\nHost: "; *post+=SERVER; *post+="\nContent-Type: application/json\nContent-Length: "
			+ String(json.length()); *post+="\n\n"; *post+=json;

#if defined(DEBUG) && defined(DEBUG_DIAG)
	debug.println(post->c_str());
#endif

	return OK;
}
