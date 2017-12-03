#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

#include <RTCZero.h>
#include "Globals.h"
#include "SystemStructs.h"
#include "CommIntfc.h"
#include "ControlIntfc.h"
#include "PositioningIntfc.h"

#ifdef DEBUG
#include "Debug.h"
#endif

//**************************************************************************************
// Scheduling constants
//**************************************************************************************
#define NUM_STATES 10
#define IDLE_INTERVAL 1	//in min
#define GPS_FIX_DELAY 3000
//**************************************************************************************


//**************************************************************************************
// State enumerations for calling the state function
// pointers in the state function array
//**************************************************************************************
typedef enum EState {
	INIT = 0,
	GPS_WARMUP,
	GPS_LOOKUP,
	GENERATE_MOTOR_COORDINATES,
	MAG_LOOKUP,
	MOT_SIG_SETUP,
	MOVE_MOTORS,
	CHECK_POSITION,
	SEND_DIAGNOSTICS,
	IDLE
}State;
//**************************************************************************************


//**************************************************************************************
#if defined(DEBUG) && defined(DEBUG_SCHED)
	static const char* stateStr[]={
			"INIT",
			"GPS_WARMUP",
			"GPS_LOOKUP",
			"GENERATE_LOOKUP_TABLE",
			"MAG_LOOKUP",
			"MOT_SIG_SETUP",
			"MOVE_MOTORS",
			"CHECK_POSITION",
			"SEND_DIAGNOSTICS",
			"IDLE"
	};
#endif
//**************************************************************************************


class Schedule{
private:
#ifdef DEBUG
	Debug debug;
#endif

	// Schedule class variables
	CommIntfc * commIntfc;
	ControlIntfc * contIntfc;
	PositioningIntfc * posIntfc;
	State nextState;
	RTCZero rtc;
//
	GPSData gData;
	CurrVoltData cvData;
	LightSensorData lsData;
	SpaData sData;
	double deg;
//
	bool inTolerance;
	bool day;
	bool night;
	bool stayIdle;

	// define function pointer type
	typedef Status (Schedule::*StateFunc)();

	// State function pointers
	// Need to be in same order as the state enum
	StateFunc States[NUM_STATES] = {
			&Schedule::InitState,
			&Schedule::GPSWarmupState,
			&Schedule::GPSLookupState,
			&Schedule::GenMotorCoordinatesState,
			&Schedule::MagLookupState,
			&Schedule::MotSigSetupState,
			&Schedule::MoveMotorsState,
			&Schedule::CheckPositionState,
			&Schedule::SendDiagnosticsState,
			&Schedule::IdleState
	};

	// state functions
	Status InitState();
	Status GPSWarmupState();
	Status GPSLookupState();
	Status GenMotorCoordinatesState();
	Status MagLookupState();
	Status MotSigSetupState();
	Status MoveMotorsState();
	Status CheckPositionState();
	Status SendDiagnosticsState();
	Status IdleState();

	// helper functions
	void GenNextState();
//	void IdleInterrupt();
public:
	Schedule();
	~Schedule();
	void IdleInterrupt();
	Status NextState();
	void RunSchedule();
};

#endif  /* _SCHEDULE_H_ */
