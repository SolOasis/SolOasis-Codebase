/*
 * PositioningModule.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: Chris
 */

#include <math.h>
#include "PositioningModule.h"

//**************************************************************************************
// ~Positioning Module Constructor~
//**************************************************************************************
PositioningModule::PositioningModule() {

}
//**************************************************************************************


//**************************************************************************************
// ~Positioning Module Destructor~
//**************************************************************************************
PositioningModule::~PositioningModule() {

}
//**************************************************************************************


//**************************************************************************************
// ~Get SPA Data~
//**************************************************************************************
Status PositioningModule::GetSPAData(GPSData * gData, SpaData* sData) {
	return spaCalc.GetSpaData(gData,sData);
}
//**************************************************************************************


//**************************************************************************************
// ~Light Sensors In Tolerance~
// Checks light sensor values to make sure no further servo rotation is needed
//**************************************************************************************
Status PositioningModule::LightSensorsInTolerance(bool* inTolerance,
		LightSensorData* lsData) {
	double vertical = lsData->voltTop - lsData->voltBottom;
	double horizontal = lsData->voltRight - lsData->voltLeft;
	if(abs(vertical)>tolerance || abs(horizontal)>tolerance) *inTolerance = false;
	else *inTolerance = true;
	return OK;
}
//**************************************************************************************


//**************************************************************************************
// ~Light Sensor Position Correction~
// Changes voltage difference into useable degree values for servo rotation
//**************************************************************************************
Status PositioningModule::LightSensorPositionCorrection(SpaData * sData, LightSensorData * lsData){
	double vertical = lsData->voltTop - lsData->voltBottom;
	double horizontal = lsData->voltRight - lsData->voltLeft;

	//TO-DO - find way to convert voltage into degree correction

	return OK;
}
//**************************************************************************************
