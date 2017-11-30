/*
 * Schedule.cpp
 *
 *  Created on: Nov 13, 2017
 *      Author: Chris
 */

#include "Schedule.h"
#include "CommModule.h"
#include "ControlModule.h"
#include "PositioningModule.h"

////////////////////////////////////////////////////////////////////////////////////////
// Function to create the POST request for
// the diagnostics module
////////////////////////////////////////////////////////////////////////////////////////
static Status CreatePostString(String * post, GPSData* gData,
		CurrVoltData* cvData, SpaData* sData, double deg) {

	// setup json object for server to read
	String json = String("");
	json +="{\"ID\": "; json+=STATION_ID; json+=", \"data\":{";
	json+="\""; json+=GPS_HOUR_ID; json+="\": "; json+=String((int)gData->hour); json+=", ";
	json+="\""; json+=GPS_MIN_ID; json+="\": "; json+=String((int)gData->minute); json+=", ";
	json+="\""; json+=GPS_SEC_ID; json+="\": "; json+=String((int)gData->second); json+=", ";
	json+="\""; json+=GPS_DAY_ID; json+="\": "; json+=String((int)gData->day); json+=", ";
	json+="\""; json+=GPS_MONTH_ID; json+="\": "; json+=String((int)gData->month); json+=", ";
	json+="\""; json+=GPS_YEAR_ID; json+="\": "; json+=String((int)gData->year); json+=", ";
	json+="\""; json+=GPS_LAT_ID; json+="\": "; json+=String(gData->latitude); json+=", ";
	json+="\""; json+=GPS_LONG_ID; json+="\": "; json+=String(gData->longitude); json+=", ";
	json+="\""; json+=GPS_ALT_ID; json+="\": "; json+=String(gData->altitude); json+="}}\r\n";

	// put POST string together
	*post+="POST "; *post+=PATH; *post+=" HTTP/1.1\r\nHost: "; *post+=SERVER; *post+="\r\nContent-Type: application/json\r\nContent-Length: "
			+ String(json.length()); *post+="\r\n\r\n"; *post+=json;

	return OK;
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
// ~Schedule constructor~
// Initializes all interfaces and variables and starts real time counter
////////////////////////////////////////////////////////////////////////////////////////
Schedule::Schedule() {
	commIntfc = new CommModule();
	contIntfc = new ControlModule();
	posIntfc = new PositioningModule();
	posIntfc = NULL;
	nextState = INIT;

	memset(&gData,0,sizeof(GPSData));
	memset(&cvData,0,sizeof(CurrVoltData));
	memset(&sData,0,sizeof(SpaData));
	deg = 0;

	inTolerance = false;
	day = false;
	night = false;
	stayIdle = true;

	rtc.begin();
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
// ~Schedule deconstructor~
////////////////////////////////////////////////////////////////////////////////////////
Schedule::~Schedule() {
	delete commIntfc;
	delete contIntfc;
	delete posIntfc;
}
////////////////////////////////////////////////////////////////////////////////////////


Status Schedule::SetupSchedule() {
	return OK;
}


////////////////////////////////////////////////////////////////////////////////////////
// ~Generate next state method~
// Method checks nextState variable and assigns next state according to
// previous value
////////////////////////////////////////////////////////////////////////////////////////
void Schedule::GenNextState(){
	switch(nextState){
	case INIT:{ nextState = GPS_WARMUP;} break;
	case GPS_WARMUP:{ nextState = GPS_LOOKUP;} break;
	case GPS_LOOKUP:{ nextState = GENERATE_MOTOR_COORDINATES;} break;
	case GENERATE_MOTOR_COORDINATES:{ nextState = MAG_LOOKUP;} break;
	case MAG_LOOKUP:{ nextState = MOT_SIG_SETUP;} break;
	case MOT_SIG_SETUP:{ nextState = MOVE_MOTORS;} break;
//	case MOVE_MOTORS:{ nextState = (inTolerance)?COLLECT_DIAGNOSTICS:CHECK_POSITION;} break;
	case MOVE_MOTORS:{ nextState = (inTolerance)?SEND_DIAGNOSTICS:CHECK_POSITION;} break;
	case CHECK_POSITION:{ nextState = MOVE_MOTORS;} break;
//	case COLLECT_DIAGNOSTICS:{ nextState = SEND_DIAGNOSTICS;} break;
	case SEND_DIAGNOSTICS:{ nextState = IDLE;} break;
	case IDLE:{
		if(night && day) nextState = GPS_WARMUP;
//		else if(night && !day) nextState = COLLECT_DIAGNOSTICS;
		else if(night && !day) nextState = SEND_DIAGNOSTICS;
		else if(!night && day) nextState = MAG_LOOKUP;
		else nextState = IDLE;
	} break;
	default:{ nextState = INIT;} break;
	}

#if defined(DEBUG) && defined(DEBUG_SCHED)
	debug.print("State: ");debug.println(stateStr[(int)nextState]);
#endif
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
// ~Interrupt for idle state~
// Interrupt changes the stayIdle variable to false and resets the RTC timer
// to 30 min later
////////////////////////////////////////////////////////////////////////////////////////
void Schedule::IdleInterrupt() {
	stayIdle = false;

	//TO-DO - Logic for day and night variables

	rtc.setAlarmTime(rtc.getHours(),
			rtc.getMinutes()+IDLE_INTERVAL,
			rtc.getSeconds());
#if defined(DEBUG) && defined(DEBUG_SCHED)
	debug.print("New interrupt time: ");
	debug.print(rtc.getHours());debug.print(":");
	debug.print(rtc.getMinutes());debug.print(":");
	debug.println(rtc.getSeconds());
#endif
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
// ~Next state increment method~
// Method runs current state, then generates next state and returns the status of
// the ran state
////////////////////////////////////////////////////////////////////////////////////////
Status Schedule::NextState() {
	Status s = (this->*States[nextState])();
	GenNextState();
	return s;
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
// ~Initial state~
////////////////////////////////////////////////////////////////////////////////////////
Status Schedule::InitState(){
	return OK;
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
// ~GPS Warm-up state~
// State to let the GPS find a fix before getting the daily time/coordinates
////////////////////////////////////////////////////////////////////////////////////////
Status Schedule::GPSWarmupState() {
	GPSData d;
	memset(&d,0,sizeof(GPSData));

#if defined(DEBUG) && defined(DEBUG_SCHED)
	debug.print("Getting GPS fix... ");
#endif

	commIntfc->EnableGPS();
	while(!d.fix){
		commIntfc->GetGPSData(&d);
#if defined(DEBUG) && defined(DEBUG_SCHED)
	debug.print('.');
#endif
	delay(GPS_FIX_DELAY);
	};

#if defined(DEBUG) && defined(DEBUG_SCHED)
	debug.println("\nGPS fix achieved!");
#endif
	return OK;
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
// ~GPS lookup state~
// Method to get GPS data and set the RTC for the day (in case system was
// moved)
////////////////////////////////////////////////////////////////////////////////////////
Status Schedule::GPSLookupState() {
	Status s;
	while(true){
		s=commIntfc->GetGPSData(&gData);
		if(s == OK) break;
	}

	//Set RTC values
	rtc.setTime(gData.hour,gData.minute,gData.second);
	rtc.setDate(gData.day,gData.month,gData.year);

#if defined(DEBUG) && defined(DEBUG_SCHED)
	debug.print("New rtc time: ");
	debug.print(rtc.getHours());debug.print(":");
	debug.print(rtc.getMinutes());debug.print(":");
	debug.println(rtc.getSeconds());
	debug.print("New rtc date: ");
	debug.print(rtc.getMonth());debug.print("/");
	debug.print(rtc.getDay());debug.print("/");
	debug.println(rtc.getYear());
#endif

	return OK;
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
// ~Generate motor coordinates state~
////////////////////////////////////////////////////////////////////////////////////////
Status Schedule::GenMotorCoordinatesState() {
	return OK;
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
// ~Magnetometer ("Compass") data lookup state~
// Recieve compass degree values
////////////////////////////////////////////////////////////////////////////////////////
Status Schedule::MagLookupState() {
	Status s;
	if((s = commIntfc->EnableMagnetometer()) != OK) return s;
	if((s= commIntfc->GetMagnetometerData(&deg)) != OK) return s;
	return OK;
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
// ~Moter signal setup state~
////////////////////////////////////////////////////////////////////////////////////////
Status Schedule::MotSigSetupState() {
	return OK;
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
// ~Motor Movement State~
////////////////////////////////////////////////////////////////////////////////////////
Status Schedule::MoveMotorsState() {
	return OK;
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
// ~Solar panel position checking state~
////////////////////////////////////////////////////////////////////////////////////////
Status Schedule::CheckPositionState() {
	return OK;
}
////////////////////////////////////////////////////////////////////////////////////////

//This state may not be necessary
//Status Schedule::CollectDiagnosticsState() {
//	return OK;
//}

////////////////////////////////////////////////////////////////////////////////////////
// ~Send diagnostics to server state~
// Create an HTTP POST string from the current data and send it to the
// diagnostics server
////////////////////////////////////////////////////////////////////////////////////////
Status Schedule::SendDiagnosticsState() {
	String post, response;
	Status s;
	if((s=CreatePostString(&post, &gData, &cvData, &sData, deg)) != OK) return s;
	return commIntfc->SendDiagnostics(&response, &post);
}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
// ~Idle state~
// A busy wait state, waits until the 30 min increment interrupt is triggered
////////////////////////////////////////////////////////////////////////////////////////
Status Schedule::IdleState() {
	//eventually code to turn everything to sleep mode
	while(stayIdle){};
	stayIdle = true;
	return OK;
}
////////////////////////////////////////////////////////////////////////////////////////
