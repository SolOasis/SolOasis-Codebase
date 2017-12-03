/*
 * Schedule.cpp
 *
 *  Created on: Nov 13, 2017
 *      Author: Chris
 */

#include <stdint.h>
#include "Schedule.h"
#include "CommModule.h"
#include "ControlModule.h"
#include "PositioningModule.h"

// Pointer to single schedule instance for interrupt to work
// properly
static Schedule * schedule = NULL;
static RTCZero * _rtc;
static bool * _day;
static bool * _night;
static bool * _idle;
static StandardTime * _sunset;
static StandardTime * _sunrise;
static uint8_t _hour, _minute, _second;

//**************************************************************************************
// Function to create the POST request for
// the diagnostics module
//**************************************************************************************
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
	json+="\""; json+=GPS_ALT_ID; json+="\": "; json+=String(gData->altitude); json+=", ";

//	json+="\""; json+=CV_PAV_ID; json+="\": "; json+=String(cvData->panelAvgVoltage); json+=", ";
//	json+="\""; json+=CV_PAC_ID; json+="\": "; json+=String(cvData->panelAvgCurrent); json+=", ";
//	json+="\""; json+=CV_PCP_ID; json+="\": "; json+=String(cvData->panelCurrPower); json+=", ";
//	json+="\""; json+=CV_PE_ID; json+="\": "; json+=String(cvData->panelEnergy); json+=", ";
//	json+="\""; json+=CV_BAV_ID; json+="\": "; json+=String(cvData->battAvgVoltage); json+=", ";
//	json+="\""; json+=CV_BAC_ID; json+="\": "; json+=String(cvData->battAvgCurrent); json+=", ";
//	json+="\""; json+=CV_BCP_ID; json+="\": "; json+=String(cvData->battCurrPower); json+=", ";
//	json+="\""; json+=CV_BE_ID; json+="\": "; json+=String(cvData->battEnergy); json+=", ";
//	json+="\""; json+=CV_CAV_ID; json+="\": "; json+=String(cvData->convAvgVoltage); json+=", ";
//	json+="\""; json+=CV_CAC_ID; json+="\": "; json+=String(cvData->convAvgCurrent); json+=", ";
//	json+="\""; json+=CV_CCP_ID; json+="\": "; json+=String(cvData->convCurrPower); json+=", ";
//	json+="\""; json+=CV_CE_ID; json+="\": "; json+=String(cvData->convEnergy); json+=", ";

	json+="\""; json+=SPA_AZI_ID; json+="\": "; json+=String(sData->azimuth); json+=", ";
	json+="\""; json+=SPA_ELEV_ID; json+="\": "; json+=String(sData->elevation); json+=", ";
	json+="\""; json+=SPA_ZEN_ID; json+="\": "; json+=String(sData->zenith); json+=", ";
	json+="\""; json+=SPA_SRISE_ID; json+="\": ";
	//setup time fields
	if(sData->sunrise.hour < 10) json+="0";
	json+=String(sData->sunrise.hour); json+=":";
	if(sData->sunrise.minute < 10) json+="0";
	json+=String(sData->sunrise.minute); json+=":";
	if(sData->sunrise.second < 10) json+="0";
	json+=String(sData->sunrise.second); json+=":"; json+=", ";
	json+="\""; json+=SPA_SSET_ID; json += "\": ";
	if(sData->sunset.hour < 10) json+="0";
	json+=String(sData->sunset.hour); json+=":";
	if(sData->sunset.minute < 10) json+="0";
	json+=String(sData->sunset.minute); json+=":";
	if(sData->sunset.second < 10) json+="0";
	json+=String(sData->sunset.second); json+=":"; json+=", ";
	json+="\""; json+=SPA_JUL_ID; json+="\": "; json+=String(sData->julianDay); json+=", ";

	json+="\""; json+=MA_DEG_ID; json+="\": "; json+=String(deg); json+=", ";

	int percent = 0;
//	if(cvData->battAvgVoltage > 12.7) percent = 100;
//	else if(cvData->battAvgVoltage > 12.4) percent = 75;
//	else if(cvData->battAvgVoltage > 12.2) percent = 50;
//	else if(cvData->battAvgVoltage > 12.0) percent = 25;

	json+="\""; json+=BATT_PERC_ID; json+="\": "; json+=String(percent); json+="%}}\r\n";

	// put POST string together
	*post+="POST "; *post+=PATH; *post+=" HTTP/1.1\r\nHost: "; *post+=SERVER; *post+="\r\nContent-Type: application/json\r\nContent-Length: "
			+ String(json.length()); *post+="\r\n\r\n"; *post+=json;

	return OK;
}
//**************************************************************************************


//**************************************************************************************
// ~Schedule interrupt~
// Void function pointer that calls the idle interrupt function of
// the scheduling object
//**************************************************************************************
void _Interrupt(){
//	_hour = _rtc->getHours();
//	_minute = _rtc->getMinutes();
//	_second = _rtc->getSeconds();
//	if(!(*_day)){
//			if(_hour > _sunrise->hour) *_day = true;
//			else if(_hour == _sunrise->hour &&
//	//				_minute >= _sunrise->minute) *_day = true;
//					_minute == _sunrise->minute) *_day = true;
//		}
//	if(!(*_night)){
//			if(_hour > _sunset->hour){
//				*_night = true;
//				*_day = false;
//			}
//			else if(_hour == _sunset->hour &&
//	//				_minute >= _sunset->minute){
//					_minute == _sunset->minute){
//				*_night = true;
//				*_day = false;
//			}
//		}
//
////		_rtc->setAlarmMinutes((_rtc->getAlarmMinutes()+IDLE_INTERVAL));
//	_rtc->setAlarmSeconds((_rtc->getAlarmSeconds()+15)%60);

	schedule->IdleInterrupt();
}
//**************************************************************************************



//**************************************************************************************
// ~Schedule constructor~
// Initializes all interfaces and variables and starts real time counter
//**************************************************************************************
Schedule::Schedule() {
	commIntfc = new CommModule();
	contIntfc = new ControlModule();
	posIntfc = new PositioningModule();
	nextState = INIT;

	memset(&gData,0,sizeof(GPSData));
	memset(&cvData,0,sizeof(CurrVoltData));
	memset(&lsData,0,sizeof(LightSensorData));
	memset(&sData,0,sizeof(SpaData));
	deg = 0;

	// Set true so that light sensor correction isn't
	// done the first motor setup
	inTolerance = true;
	day = false;
	night = false;
	stayIdle = false;

	// Set up sunrise and sunset times for interrupt
	sData.sunrise.hour = 6;
	sData.sunrise.minute = 0;
	sData.sunrise.second = 0;

	sData.sunset.hour = 18;
	sData.sunset.minute = 0;
	sData.sunset.second = 0;

	//TESTING ONLY
	day = true;
	sData.sunrise.hour = 0;
	sData.sunrise.minute = 3;
	sData.sunrise.second = 0;

	sData.sunset.hour = 0;
	sData.sunset.minute = 2;
	sData.sunset.second = 0;

	// May do this for testing, may be permanent
	//GLITCHY
//	commIntfc->EnableWiFi();

	// set static variables for interrupt
	if(schedule == NULL) schedule = this;
	if(_rtc == NULL) _rtc = &rtc;
	_day = &day;
	_night = &night;
	_idle = &stayIdle;
	_sunrise = &(sData.sunrise);
	_sunset = &(sData.sunset);

	rtc.begin();
	rtc.setTime(0,0,0);
	rtc.enableAlarm(rtc.MATCH_MMSS);
	rtc.attachInterrupt((voidFuncPtr)_Interrupt);
}
//**************************************************************************************


//**************************************************************************************
// ~Schedule deconstructor~
//**************************************************************************************
Schedule::~Schedule() {
	delete commIntfc;
	delete contIntfc;
	delete posIntfc;
}
//**************************************************************************************


void Schedule::RunSchedule(){
	while(true){
		NextState();
//		delay(1000);
	}
}


//**************************************************************************************
// ~Generate next state method~
// Method checks nextState variable and assigns next state according to
// previous value
//**************************************************************************************
void Schedule::GenNextState(){
	State prevState = nextState;

	switch(nextState){
	case INIT:{ nextState = GPS_WARMUP;} break;
	case GPS_WARMUP:{ nextState = GPS_LOOKUP;} break;
	case GPS_LOOKUP:{ nextState = GENERATE_MOTOR_COORDINATES;} break;
	case GENERATE_MOTOR_COORDINATES:{ nextState = MAG_LOOKUP;} break;
	case MAG_LOOKUP:{ nextState = MOT_SIG_SETUP;} break;
	case MOT_SIG_SETUP:{ nextState = MOVE_MOTORS;} break;
	case MOVE_MOTORS:{ nextState = CHECK_POSITION;} break;
	case CHECK_POSITION:{ nextState = (inTolerance)?SEND_DIAGNOSTICS:MOT_SIG_SETUP;} break;
	case SEND_DIAGNOSTICS:{ nextState = IDLE;} break;
	case IDLE:{
		if(stayIdle) nextState = IDLE;
		else if(night && day) nextState = GPS_WARMUP;
		else if(night && !day) nextState = SEND_DIAGNOSTICS;
		else if(!night && day) nextState = MAG_LOOKUP;
		else nextState = IDLE;
	} break;
	default:{ nextState = INIT;} break;
	}

#if defined(DEBUG) && defined(DEBUG_SCHED)
	if(prevState != nextState) {
		debug.print("State: ");debug.println(stateStr[(int)nextState]);
	}
#endif
}
//**************************************************************************************


//**************************************************************************************
// ~Interrupt for idle state~
// Interrupt changes the stayIdle variable to false and resets the RTC timer
// to 30 min later
//**************************************************************************************
void Schedule::IdleInterrupt() {
	stayIdle = false;

#if defined(DEBUG) && defined(DEBUG_SCHED)
	debug.println("RTC INTERRUPT");
#endif

	uint8_t hour = rtc.getHours();
	uint8_t minute = rtc.getMinutes();
	uint8_t second = rtc.getSeconds();

	//TESTING ONLY
#if defined(DEBUG) && defined(DEBUG_SCHED)
	debug.print("-------------------------\r\nRTC: ");
	if(hour < 10)debug.print("0");
	debug.print(hour);debug.print(":");
	if(minute < 10)debug.print("0");
	debug.print(minute);debug.print(":");
	if(second < 10)debug.print("0");
	debug.println(second);

	debug.print("RTC Alarm: ");
	if(rtc.getAlarmHours() < 10)debug.print("0");
	debug.print(rtc.getAlarmHours());debug.print(":");
	if(rtc.getAlarmMinutes() < 10)debug.print("0");
	debug.print(rtc.getAlarmMinutes());debug.print(":");
	if(rtc.getAlarmSeconds() < 10)debug.print("0");
	debug.println(rtc.getAlarmSeconds());

	debug.print("Sunrise: ");
	if(sData.sunrise.hour < 10)debug.print("0");
	debug.print(sData.sunrise.hour);debug.print(":");
	if(sData.sunrise.minute < 10)debug.print("0");
	debug.print(sData.sunrise.minute);debug.print(":");
	if(sData.sunrise.second < 10)debug.print("0");
	debug.println(sData.sunrise.second);

	debug.print("Sunset: ");
	if(sData.sunset.hour < 10)debug.print("0");
	debug.print(sData.sunset.hour);debug.print(":");
	if(sData.sunset.minute < 10)debug.print("0");
	debug.print(sData.sunset.minute);debug.print(":");
	if(sData.sunset.second < 10)debug.print("0");
	debug.println(sData.sunset.second);
	debug.print("Day is "); debug.println((day)?"TRUE":"FALSE");
	debug.print("Night is "); debug.println((night)?"TRUE":"FALSE");
#endif

	if(!day){
		if(hour > sData.sunrise.hour) day = true;
		else if(hour == sData.sunrise.hour &&
//				minute >= sData.sunrise.minute) day = true;
				minute == sData.sunrise.minute) day = true;
#if defined(DEBUG) && defined(DEBUG_SCHED)
		if(day) debug.println("Day variable triggered!");
#endif
	}

	if(!night){
		if(hour > sData.sunset.hour){
			night = true;
			day = false;
		}
		else if(hour == sData.sunset.hour &&
//				minute >= sData.sunset.minute){
				minute == sData.sunset.minute){
			night = true;
			day = false;
		}
#if defined(DEBUG) && defined(DEBUG_SCHED)
		if(night) debug.println("Night variable triggered!");
#endif
	}

#if defined(DEBUG) && defined(DEBUG_SCHED)
	debug.print("New interrupt time: ");
	if(rtc.getAlarmHours() + (minute+IDLE_INTERVAL)/60 < 10)debug.print("0");
	debug.print(rtc.getAlarmHours()+(rtc.getAlarmMinutes()+IDLE_INTERVAL)/60);debug.print(":");
	if((rtc.getAlarmMinutes()+IDLE_INTERVAL)%60 < 10)debug.print("0");
	debug.print((rtc.getAlarmMinutes()+IDLE_INTERVAL)%60);debug.print(":");
	if(rtc.getAlarmSeconds() < 10)debug.print("0");
	debug.println(rtc.getAlarmSeconds());
#endif

	rtc.setAlarmHours(rtc.getAlarmHours()+(rtc.getAlarmMinutes()+IDLE_INTERVAL)/60);
	rtc.setAlarmMinutes((rtc.getAlarmMinutes()+IDLE_INTERVAL)%60);

}
//**************************************************************************************


//**************************************************************************************
// ~Next state increment method~
// Method runs current state, then generates next state and returns the status of
// the ran state
//**************************************************************************************
Status Schedule::NextState() {
#if defined(DEBUG) && defined (DEBUG_SCHED)
	if(!stayIdle){
		debug.print("Running state ");
		debug.print(stateStr[nextState]);
		debug.println("...");
	}
#endif
	Status s = (this->*States[nextState])();
	GenNextState();
	return s;
}
//**************************************************************************************


//**************************************************************************************
// ~Initial state~
// Entry point for state machine
//**************************************************************************************
Status Schedule::InitState(){
	// reset rtc
//	rtc.setTime(0,0,0);
	return OK;
}
//**************************************************************************************


//**************************************************************************************
// ~GPS Warm-up state~
// State to let the GPS find a fix before getting the daily time/coordinates
//**************************************************************************************
Status Schedule::GPSWarmupState() {

	//FOR TEST ONLY
	night = false;
	return OK;

//	// State reached, so it is no longer night
//	night = false;
//
//	GPSData d;
//	memset(&d,0,sizeof(GPSData));
//
//#if defined(DEBUG) && defined(DEBUG_SCHED)
//	debug.print("Getting GPS fix... ");
//#endif
//
//	commIntfc->EnableGPS();
//	while(!d.fix){
//		commIntfc->GetGPSData(&d);
//#if defined(DEBUG) && defined(DEBUG_SCHED)
//		debug.print('.');
//#endif
//		delay(GPS_FIX_DELAY);
//	};
//
//#if defined(DEBUG) && defined(DEBUG_SCHED)
//	debug.println("\r\nGPS fix achieved!");
//#endif
//	return OK;
}
//**************************************************************************************


//**************************************************************************************
// ~GPS lookup state~
// Method to get GPS data and set the RTC for the day (in case system was
// moved)
//**************************************************************************************
Status Schedule::GPSLookupState() {

	//TESTING ONLY
	rtc.setAlarmHours(rtc.getHours()+(rtc.getAlarmMinutes()+IDLE_INTERVAL)/60);
	rtc.setAlarmMinutes((rtc.getMinutes()+IDLE_INTERVAL)%60);
	return OK;

//	Status s;
//	while(true){
//		s=commIntfc->GetGPSData(&gData);
//		if(s == OK) break;
//	}
//
//	//Set RTC values
//	rtc.setTime(gData.hour,gData.minute,gData.second);
//	rtc.setDate(gData.day,gData.month,gData.year);
//
//	uint8_t hour = rtc.getHours();
//	uint8_t minute = rtc.getMinutes();
//	uint8_t second = rtc.getSeconds();
//
//		//Reset increment timer
//		rtc.setAlarmTime(hour, minute+IDLE_INTERVAL, second);
//
//#if defined(DEBUG) && defined(DEBUG_SCHED)
//	debug.print("New rtc time: ");
//	if(hour < 10)debug.print("0");
//	debug.print(hour);debug.print(":");
//	if(minute < 10)debug.print("0");
//	debug.print(minute);debug.print(":");
//	if(second < 10)debug.print("0");
//	debug.println(second);
//	debug.print("New rtc date: ");
//	debug.print(rtc.getMonth());debug.print("/");
//	debug.print(rtc.getDay());debug.print("/");
//	debug.println(rtc.getYear());
//#endif
//
//	return OK;
}
//**************************************************************************************


//**************************************************************************************
// ~Generate motor coordinates state~
//**************************************************************************************
Status Schedule::GenMotorCoordinatesState() {
	//TESTING ONLY
	return OK;

//	gData.hour = rtc.getHours();
//	gData.minute = rtc.getMinutes();
//	gData.second = rtc.getSeconds();
//
//	return posIntfc->GetSPAData(&gData, &sData);
}
//**************************************************************************************


//**************************************************************************************
// ~Magnetometer ("Compass") data lookup state~
// Recieve compass degree values
//**************************************************************************************
Status Schedule::MagLookupState() {

	//TESTING ONLY
//	return OK;

	Status s;
	if((s = commIntfc->EnableMagnetometer()) != OK) return s;
	if((s= commIntfc->GetMagnetometerData(&deg)) != OK) return s;
	if((s= commIntfc->DisableMagnetometer()) != OK) return s;
	return OK;
}
//**************************************************************************************


//**************************************************************************************
// ~Moter signal setup state~
//**************************************************************************************
Status Schedule::MotSigSetupState() {

	if(!inTolerance) return posIntfc->LightSensorPositionCorrection(&sData, &lsData);
	return OK;
}
//**************************************************************************************


//**************************************************************************************
// ~Motor Movement State~
//**************************************************************************************
Status Schedule::MoveMotorsState() {
	return contIntfc->rotateMotors(sData.azimuth, sData.elevation);
}
//**************************************************************************************


//**************************************************************************************
// ~Solar panel position checking state~
//**************************************************************************************
Status Schedule::CheckPositionState() {

	//TESTING ONLY

	inTolerance = !inTolerance;

	return OK;

	Status s;
	if((s = commIntfc->GetLightSensorData(&lsData)) != OK) return s;
	if((s = posIntfc->LightSensorsInTolerance(&inTolerance, &lsData)) != OK) return s;
	return OK;
}
//**************************************************************************************


//**************************************************************************************
// ~Send diagnostics to server state~
// Create an HTTP POST string from the current data and send it to the
// diagnostics server
//**************************************************************************************
Status Schedule::SendDiagnosticsState() {

	stayIdle = true;
	return OK;

	String post, response;
	Status s;
	gData.hour = rtc.getAlarmHours();
	gData.minute = rtc.getMinutes();
	gData.second = rtc.getSeconds();
	if((s=CreatePostString(&post, &gData, &cvData, &sData, deg)) != OK) return s;
	//if((s=commIntfc->EnableWiFi()) != OK) return s;
	if((s=commIntfc->SendDiagnostics(&response, &post)) != OK) return s;
	//return commIntfc->DisableWiFi();
	return OK;
}
//**************************************************************************************


//**************************************************************************************
// ~Idle state~
// A busy wait state, waits until the 30 min increment interrupt is triggered
//**************************************************************************************
Status Schedule::IdleState() {
	// busy waiting doesn't work, so just do nothing
	// logic to escape idle is somewhere else
	return OK;
}
//**************************************************************************************
