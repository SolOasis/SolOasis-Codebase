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

#define NUM_STATES 12
#define IDLE_INTERVAL 30	//in min
#define GPS_FIX_DELAY 3000

typedef enum EState {
	INIT = 0,
	GPS_WARMUP,
	GPS_LOOKUP,
	GENERATE_LOOKUP_TABLE,
	MAG_LOOKUP,
	MOT_SIG_SETUP,
	MOVE_MOTORS,
	CHECK_POSITION,
//	COLLECT_DIAGNOSTICS,
	SEND_DIAGNOSTICS,
	IDLE
}State;

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
//			"COLLECT_DIAGNOSTICS",
			"SEND_DIAGNOSTICS",
			"IDLE"
	};
#endif

class Schedule{
private:
#ifdef DEBUG
	Debug debug;
#endif

	CommIntfc * commIntfc;
	ControlIntfc * contIntfc;
	PositioningIntfc * posIntfc;
	State nextState;
	RTCZero rtc;

	GPSData gData;
	CurrVoltData cvData;
	SpaData sData;
	double deg;

	bool inTolerance;
	bool day;
	bool night;
	bool stayIdle;

	typedef Status (Schedule::*StateFunc)();

	// Need to be in same order as the state enum
	StateFunc States[NUM_STATES] = {
			&Schedule::InitState,
			&Schedule::GPSWarmupState,
			&Schedule::GPSLookupState,
			&Schedule::GenLookupTableState,
			&Schedule::MagLookupState,
			&Schedule::MotSigSetupState,
			&Schedule::MoveMotorsState,
			&Schedule::CheckPositionState,
//			&Schedule::CollectDiagnosticsState,
			&Schedule::SendDiagnosticsState,
			&Schedule::IdleState
	};

	Status InitState();
	Status GPSWarmupState();
	Status GPSLookupState();
	Status GenLookupTableState();
	Status MagLookupState();
	Status MotSigSetupState();
	Status MoveMotorsState();
	Status CheckPositionState();
	Status CollectDiagnosticsState();
	Status SendDiagnosticsState();
	Status IdleState();

	void GenNextState();
	void IdleInterrupt();
	void MorningInterrupt();
	void NightInterrupt();
public:
	Schedule();
	~Schedule();
	Status SetupSchedule();
	Status NextState();
};

#endif  /* _SCHEDULE_H_ */
