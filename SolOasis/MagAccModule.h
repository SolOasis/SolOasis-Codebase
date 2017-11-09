/*
 * MagAccModule.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#ifndef _MAG_ACC_MODULE_H_
#define _MAG_ACC_MODULE_H_

//#include <Wire.h>
#include <inttypes.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include "Globals.h"
#include "SystemStructs.h"
#include "Ports.h"

#ifdef DEBUG
#include "Debug.h"
#endif

#define MAG_ID 12345

class MagAccModule{
private:
	static bool enabled;
	static Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(MAG_ID);
	static sensor_t sensor;
	static sensors_event_t event;
	double ConvertDegrees(double x, double y, double z);

#ifdef DEBUG
	Debug debug;
#endif
public:
	MagAccModule();
	~MagAccModule();
    Status EnableModule();
    Status DisableModule();
    Status GetMagData(double * degrees);
};

#endif /* _MAG_ACC_MODULE_H_ */
