#ifndef _CONTROL_INTFC_H_
#define _CONTROL_INTFC_H_

class ControlIntfc {
  public:
    virtual ~ControlIntfc(){};
    virtual int rotateHorizontal(int8_t dgr);
    virtual int rotateVertical(int8_t dgr);
};

#endif /* _CONTROL_INTFC_H_ */
