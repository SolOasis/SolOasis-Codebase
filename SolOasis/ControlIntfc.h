#ifndef _CONTROL_INTFC_H_
#define _CONTROL_INTFC_H_

#include <inttypes.h>
#include "SystemStructs.h"

class ControlIntfc {
  public:
    virtual ~ControlIntfc(){};
    virtual Status rotateHorizontal(int16_t dgr) = 0;
    virtual Status rotateVertical(int16_t dgr) = 0;
};

#endif /* _CONTROL_INTFC_H_ */
