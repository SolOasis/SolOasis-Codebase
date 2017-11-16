/*
 * LightSensorModule.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#ifndef _LIGHT_SENSOR_MODULE_H_
#define _LIGHT_SENSOR_MODULE_H_

#include "Globals.h"
#include "SystemStructs.h"
#include "Ports.h"

#ifdef DEBUG
#include "Debug.h"
#endif

class LightSensorModule{
private:
#ifdef DEBUG
	Debug debug;
#endif

public:
	LightSensorModule();
	~LightSensorModule();
};

#endif /* _LIGHT_SENSOR_MODULE_H_ */