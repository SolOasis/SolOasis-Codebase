#ifndef _CONTROL_MODULE_H_
#define _CONTROL_MODULE_H_

#include "ControlIntfc.h"

class ControlModule : public ControlIntfc {
  private:

  public:
    ControlModule();
    ~ControlModule();
    int rotateHorizontal(int8_t dgr);
    int rotateVertical(int8_t dgr);
};

#endif /* _CONTROL_MODULE_H */
