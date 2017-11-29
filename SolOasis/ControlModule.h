#ifndef _CONTROL_MODULE_H_
#define _CONTROL_MODULE_H_

#include "ControlIntfc.h"

class ControlModule : public ControlIntfc {
  private:
    Status rotateHorizontal(int dgr);
    Status rotateVertical(int dgr);

  public:
    ControlModule();
    ~ControlModule();
    Status rotateMotors(int AzimuthDgr, int ElevationDgr);
};

#endif /* _CONTROL_MODULE_H */
