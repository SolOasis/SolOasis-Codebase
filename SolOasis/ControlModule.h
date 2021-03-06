/*
 * ControlModule.h
 *
 *  Created on: Nov 9, 2017
 *      Author: Allen
 */
#ifndef _CONTROL_MODULE_H_
#define _CONTROL_MODULE_H_

#include "ControlIntfc.h"
#include "Globals.h"
#include "SystemStructs.h"
#include "Ports.h"

#ifdef DEBUG
#include "Debug.h"
#endif

#define SERVO_DELAY_TIME 150
#define SERVO_DELAY_RATIO 10

#define STOP 90

class ControlModule : public ControlIntfc {
  private:
#ifdef DEBUG
	Debug debug;
#endif
    Status rotateHorizontal(int dgr);
    Status rotateVertical(int dgr);
    void breakMotors(bool hor, bool ver);
    void waitMovementAndRecord(int horDiff, int verDiff);
    int lastHorizontalDgr;
    int lastVerticalDgr;

  public:
    ControlModule();
    ~ControlModule();
    Status rotateMotors(int AzimuthDgr, int ElevationDgr);
};

#endif /* _CONTROL_MODULE_H */
