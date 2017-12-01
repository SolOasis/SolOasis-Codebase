/*
 * CurrVoltModule.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#ifndef _CURR_VOLT_MODULE_H_
#define _CURR_VOLT_MODULE_H_

#include "Globals.h"
#include "SystemStructs.h"
#include "Ports.h"

#ifdef DEBUG
#include "Debug.h"
#endif

class CurrVoltModule{
private:

#ifdef DEBUG
	Debug debug;
#endif

public:
	CurrVoltModule();
	~CurrVoltModule();
	Status ReceiveData(CurrVoltData * cvData);
};



#endif /* _CURR_VOLT_MODULE_H_ */
