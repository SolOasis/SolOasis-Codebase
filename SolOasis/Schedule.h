#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

#include "Globals.h"
#include "SystemStructs.h"
#include "CommIntfc.h"
#include "ControlIntfc.h"
#include "PositioningIntfc.h"

#define NUM_STATES 12

typedef enum EState {
	INIT = 0,
	GPS_WARMUP,
	GPS_LOOKUP,
	GENERATE_LOOKUP_TABLE,
	MAG_LOOKUP,
	MOT_SIG_SETUP,
	MOVE_MOTORS,
	CHECK_POSITION,
	COLLECT_DIAGNOSTICS,
	SEND_DIAGNOSTICS,
	IDLE
}State;

class Schedule{
private:
	CommIntfc * commIntfc;
	ControlIntfc * contIntfc;
	PositioningIntfc * posIntfc;
	State nextState;

	GPSData gData;
	CurrVoltData cvData;
	double deg;

	bool inTolerance;
	bool day;
	bool night;

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
			&Schedule::CollectDiagnosticsState,
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
public:
	Schedule();
	~Schedule();
	Status SetupSchedule();
	Status NextState();
};

#endif  /* _SCHEDULE_H_ */
