#ifndef _CONTROL_MODULE_H_
#define _CONTROL_MODULE_H_

#include "ControlIntfc.h"
#include "Globals.h"

#ifdef DEBUG
#include "Debug.h"
#endif

class ControlModule : public ControlIntfc {
  private:
#ifdef DEBUG
	Debug debug;
#endif

    Status rotateHorizontal(int dgr);
    Status rotateVertical(int dgr);

  public:
    ControlModule();
    ~ControlModule();
    Status rotateMotors(int AzimuthDgr, int ElevationDgr);
};

#endif /* _CONTROL_MODULE_H */
