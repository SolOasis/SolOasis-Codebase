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

Schedule::Schedule() {
	commIntfc = new CommModule();
	contIntfc = new ControlModule();
	posIntfc = new PositioningModule();
	posIntfc = NULL;
	nextState = INIT;

	memset(&gData,0,sizeof(GPSData));
	memset(&cvData,0,sizeof(CurrVoltData));
	deg = 0;

	inTolerance = false;
	day = false;
	night = false;
	stayIdle = true;

	rtc.begin();
}

Schedule::~Schedule() {
	delete commIntfc;
	delete contIntfc;
	delete posIntfc;
}

Status Schedule::SetupSchedule() {
	return OK;
}

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

void Schedule::IdleInterrupt() {
	stayIdle = false;
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

void Schedule::MorningInterrupt() {
	day = true;
}

void Schedule::NightInterrupt() {
	night = true;
}

Status Schedule::NextState() {
	Status s = (this->*States[nextState])();
	GenNextState();
	return s;
}

Status Schedule::InitState(){
	return OK;
}

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

Status Schedule::GenMotorCoordinatesState() {
	return OK;
}

Status Schedule::MagLookupState() {
	Status s;
	if((s = commIntfc->EnableMagnetometer()) != OK) return s;
	if((s= commIntfc->GetMagnetometerData(&deg)) != OK) return s;
	return OK;
}

Status Schedule::MotSigSetupState() {
	return OK;
}

Status Schedule::MoveMotorsState() {
	return OK;
}

Status Schedule::CheckPositionState() {
	return OK;
}

//This state may not be necessary
//Status Schedule::CollectDiagnosticsState() {
//	return OK;
//}

Status Schedule::SendDiagnosticsState() {
	return commIntfc->SendDiagnostics(&gData,&cvData,&sData,deg);
}

Status Schedule::IdleState() {
	//eventually code to turn everything to sleep mode
	while(stayIdle){};
	stayIdle = true;
	return OK;
}
