/*
 * Schedule.cpp
 *
 *  Created on: Nov 13, 2017
 *      Author: Chris
 */

#include "Schedule.h"
#include "CommModule.h"
#include "ControlModule.h"

// ---State Function Prototypes---
// These are not included in schedule class to allow
// their use in a function pointer array
//Status InitState();

// -------------------------------

//typedef Status (*StateFunc)();
//
//const StateFunc States[] = {
//		InitState
//};

Schedule::Schedule() {
	commIntfc = new CommModule();
	contIntfc = new ControlModule();
	posIntfc = NULL;
	nextState = INIT;

	memset(&gData,0,sizeof(GPSData));
	memset(&cvData,0,sizeof(CurrVoltData));
	deg = 0;

	inTolerance = false;
	day = false;
	night = false;
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
	case GPS_LOOKUP:{ nextState = GENERATE_LOOKUP_TABLE;} break;
	case GENERATE_LOOKUP_TABLE:{ nextState = MAG_LOOKUP;} break;
	case MAG_LOOKUP:{ nextState = MOT_SIG_SETUP;} break;
	case MOT_SIG_SETUP:{ nextState = MOVE_MOTORS;} break;
	case MOVE_MOTORS:{ nextState = (inTolerance)?COLLECT_DIAGNOSTICS:CHECK_POSITION;} break;
	case CHECK_POSITION:{ nextState = MOVE_MOTORS;} break;
	case COLLECT_DIAGNOSTICS:{ nextState = SEND_DIAGNOSTICS;} break;
	case SEND_DIAGNOSTICS:{ nextState = IDLE;} break;
	case IDLE:{
		if(night && day) nextState = GPS_WARMUP;
		else if(night && !day) nextState = COLLECT_DIAGNOSTICS;
		else if(!night && day) nextState = MAG_LOOKUP;
		else nextState = IDLE;
	} break;
	default:{ nextState = INIT;} break;
	}
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

	commIntfc->EnableGPS();
	while(!d.fix){commIntfc->GetGPSData(&d);};

	return OK;
}

Status Schedule::GPSLookupState() {
	Status s;
	while(true){
		s=commIntfc->GetGPSData(&gData);
		if(s == OK) break;
	}

	return OK;
}

Status Schedule::GenLookupTableState() {
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

Status Schedule::CollectDiagnosticsState() {
	return OK;
}

Status Schedule::SendDiagnosticsState() {
	return OK;
}

Status Schedule::IdleState() {
	return OK;
}

//Status InitState(){
//	return OK;
//}
