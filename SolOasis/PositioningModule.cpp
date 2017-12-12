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
	int vertical = lsData->voltTop - lsData->voltBottom;
	int horizontal = lsData->voltRight - lsData->voltLeft;
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
	int verticalDiff = lsData->voltTop - lsData->voltBottom;
	int horizontalDiff = lsData->voltRight - lsData->voltLeft;
	int degree_to_change = 3;
	//TO-DO - find way to convert voltage into degree correction
	if (horizontalDiff < 0) {
		sData->azimuth += degree_to_change;
		if (sData->azimuth > 180)
			sData->azimuth = 180;
	}
	else if (horizontalDiff > 0) {
		sData->azimuth -= degree_to_change;
		if (sData->azimuth < 0)
			sData->azimuth = 0;
	}

	if (verticalDiff < 0) {
		sData->elevation += degree_to_change;
		if (sData->elevation > 180)
			sData->elevation = 180;
	}
	else if (verticalDiff > 0) {
		sData->elevation -= degree_to_change;
		if (sData->elevation < 0)
			sData->elevation = 0;
	}
	return OK;
}
//**************************************************************************************
