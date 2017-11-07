#ifndef _CONTROL_MODULE_H_
#define _CONTROL_MODULE_H_

#include "ControlIntfc.h"

class ControlModule : public ControlIntfc {
  private:

  public:
    ControlModule();
    ~ControlModule();
    Status rotateHorizontal(int8_t dgr);
    Status rotateVertical(int8_t dgr);
};

#endif /* _CONTROL_MODULE_H */
