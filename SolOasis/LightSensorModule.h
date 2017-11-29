/*
 * LightSensorModule.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Allen, Chris
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
  Status GetLightSensorData(LightSensorData * lsData);
};

#endif /* _LIGHT_SENSOR_MODULE_H_ */
