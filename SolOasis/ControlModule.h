#ifndef _CONTROL_MODULE_H_
#define _CONTROL_MODULE_H_

#include "ControlIntfc.h"

class ControlModule : public ControlIntfc {
  private:

  public:
    ControlModule();
    ~ControlModule();
    Status rotateHorizontal(int16_t dgr);
    Status rotateVertical(int16_t dgr);
};

#endif /* _CONTROL_MODULE_H */
