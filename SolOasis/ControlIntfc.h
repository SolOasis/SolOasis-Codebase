#ifndef _CONTROL_INTFC_H_
#define _CONTROL_INTFC_H_

#include <inttypes.h>
#include "SystemStructs.h"

class ControlIntfc {
  public:
    virtual ~ControlIntfc(){};
    virtual Status rotateHorizontal(int8_t dgr);
    virtual Status rotateVertical(int8_t dgr);
};

#endif /* _CONTROL_INTFC_H_ */
