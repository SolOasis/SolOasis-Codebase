#ifndef _CONTROL_INTFC_H_
#define _CONTROL_INTFC_H_

#include <inttypes.h>
#include "SystemStructs.h"

class ControlIntfc {
  private:
    virtual Status rotateHorizontal(int dgr) = 0;
    virtual Status rotateVertical(int dgr) = 0;
  public:
    virtual ~ControlIntfc(){};
    virtual Status rotateMotors(int AzimuthDgr, int ElevationDgr) = 0;

};

#endif /* _CONTROL_INTFC_H_ */
