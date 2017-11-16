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
	currState = INIT;
}

Schedule::~Schedule() {
	delete commIntfc;
	delete contIntfc;
	delete posIntfc;
}

Status Schedule::SetupSchedule() {
	return OK;
}

Status Schedule::NextState() {
	return this->States[currState]();
}

Status Schedule::InitState(){
	return OK;
}

Status Schedule::GPSLookupState() {
	return OK;
}

Status Schedule::GenLookupTableState() {
	return OK;
}

Status Schedule::MagLookupState() {
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
