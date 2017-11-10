/*
 * MagAccModule.cpp
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#include <math.h>
#include "MagAccModule.h"

#define PI 3.14159265

MagAccModule::MagAccModule() {
}

MagAccModule::~MagAccModule() {
}

double MagAccModule::ConvertDegrees(double x, double y, double z) {
	double val = atan2(x,y) * 180 / PI;
	if(val < 0){
		val+=360;
	}
	return val;
}


Status MagAccModule::EnableModule() {
	mag.getSensor(&sensor);
	mag.enableAutoRange(true);
	if(!mag.begin()){
#ifdef DEBUG
		debug.println("Magnetometer Error: No LSM303 detected");
#endif
		return MA_DEVICENOTDETECTED;
	}

#ifdef DEBUG
	debug.println("Magnetometer Info:");
	debug.print  ("Sensor:       "); debug.println(sensor.name);
	debug.print  ("Driver Ver:   "); debug.println(sensor.version);
	debug.print  ("Unique ID:    "); debug.println(sensor.sensor_id);
	debug.print  ("Max Value:    "); debug.print(sensor.max_value); debug.println(" uT");
	debug.print  ("Min Value:    "); debug.print(sensor.min_value); debug.println(" uT");
	debug.print  ("Resolution:   "); debug.print(sensor.resolution); debug.println(" uT");
	debug.println();
#endif
	return OK;
}

Status MagAccModule::DisableModule() {
	#ifdef DEBUG
	  debug.println("Magnetometer cannot be disabled");
	#endif
	  return OK;
}

Status MagAccModule::GetMagData(double* degrees) {
	mag.getEvent(&event);
	*degrees = ConvertDegrees(event.magnetic.x, event.magnetic.y, event.magnetic.z);
	return OK;
}

