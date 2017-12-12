/*
 * LightSensorModule.cpp
 *
 *  Created on: Nov 9, 2017
 *      Author: Allen, Chris
 */

#include "LightSensorModule.h"

//**************************************************************************************
// ~Light Sensor Module Constructor~
//**************************************************************************************
LightSensorModule::LightSensorModule() {
}
//**************************************************************************************


//**************************************************************************************
// ~Light Sensor Module Destructor~
//**************************************************************************************
LightSensorModule::~LightSensorModule() {
}
//**************************************************************************************


//**************************************************************************************
// ~Get Light Sensor Data~
// Gets data from analog inputs for light sensors
//**************************************************************************************
Status LightSensorModule::GetLightSensorData(LightSensorData * lsData) {

	// get sensor voltages
	int voltTopLeft = analogRead(PRTopLeftPin);
	int voltTopRight = analogRead(PRTopRightPin);
	int voltBottomLeft = analogRead(PRBottomLeftPin);
	int voltBottomRight = analogRead(PRBottomRightPin);

	// get averages for vertical and horizontal directions
	lsData->voltTop = (voltTopLeft + voltTopRight) / 2;
	lsData->voltBottom = (voltBottomLeft + voltBottomRight) / 2;
	lsData->voltLeft = (voltTopLeft + voltBottomLeft) / 2;
	lsData->voltRight = (voltTopRight + voltBottomRight) / 2;

#if defined(DEBUG) && defined(DEBUG_LS)
	debug.print("Sensor Top Left:     "); debug.println(voltTopLeft);
	debug.print("Sensor Top Right:    "); debug.println(voltTopRight);
	debug.print("Sensor Bottom Left:  "); debug.println(voltBottomLeft);
	debug.print("Sensor Bottom Right: "); debug.println(voltBottomRight);
	debug.print("Volt Top:    "); debug.println(lsData->voltTop);
	debug.print("Volt Bottom: "); debug.println(lsData->voltBottom);
	debug.print("Volt Left:   "); debug.println(lsData->voltLeft);
	debug.print("Volt Right:  "); debug.println(lsData->voltRight);
#endif
	return OK;
}
//**************************************************************************************
