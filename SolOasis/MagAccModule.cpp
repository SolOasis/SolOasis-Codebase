/*
 * MagAccModule.cpp
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#include <math.h>
#include "MagAccModule.h"

#define PI 3.14159265

//**************************************************************************************
// ~Magnetometer-Accelerometer Module Constructor~
//**************************************************************************************
MagAccModule::MagAccModule() {

}
//**************************************************************************************


//**************************************************************************************
// ~Magnetometer-Accelerometer Module Destructor~
//**************************************************************************************
MagAccModule::~MagAccModule() {

}
//**************************************************************************************


//**************************************************************************************
// ~Convert Degrees~
// Change degrees for x, y, and z coordinates into x-y plane compass degrees
//**************************************************************************************
double MagAccModule::ConvertDegrees(double x, double y, double z) {
	double val = (atan2(x,y) * 180 ) / PI;

#if defined(DEBUG) && defined(DEBUG_MA)
	debug.print("Unaltered val: "); debug.println(val);
#endif

	if(val < 0){
		val+=360;
	}
	return val;
}
//**************************************************************************************


//**************************************************************************************
// ~Enable Manetometer-Accelerometer Module~
// Sends sensor initialization data
//**************************************************************************************
Status MagAccModule::EnableModule() {
	mag.getSensor(&sensor);
	mag.enableAutoRange(true);
	if(!mag.begin()){
#if defined(DEBUG) && defined(DEBUG_MA)
		debug.println("Magnetometer Error: No LSM303 detected");
#endif
		return MA_DEVICE_NOT_DETECTED;
	}

#if defined(DEBUG) && defined(DEBUG_MA)
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
//**************************************************************************************


//**************************************************************************************
// ~Disable Magnetometer-Accelerometer Module~
// Currently not implemented
//**************************************************************************************
Status MagAccModule::DisableModule() {
	#if defined(DEBUG) && defined(DEBUG_MA)
	  debug.println("Magnetometer cannot be disabled");
	#endif
	  return OK;
}
//**************************************************************************************


//**************************************************************************************
// ~Get Magnetometer Data~
// Gets magnetic field data from sensor
//**************************************************************************************
Status MagAccModule::GetMagData(double* degrees) {
	mag.getEvent(&event);
	*degrees = ConvertDegrees(event.magnetic.x, event.magnetic.y, event.magnetic.z);
#if defined(DEBUG) && defined(DEBUG_MA)
	debug.print("magnetic x: "); debug.println(event.magnetic.x);
	debug.print("magnetic y: "); debug.println(event.magnetic.y);
	debug.print("magnetic z: "); debug.println(event.magnetic.z);
#endif
	return OK;
}
//**************************************************************************************
