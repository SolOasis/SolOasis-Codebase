/*
 * PositioningModule.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: Chris
 */

#include <math.h>
#include "PositioningModule.h"

PositioningModule::PositioningModule() {
}

PositioningModule::~PositioningModule() {
}

Status PositioningModule::GetSPAData(GPSData * gData, SpaData* sData) {
	return spaCalc.GetSpaData(gData,sData);
}

Status PositioningModule::LightSensorsInTolerance(bool* inTolerance,
		LightSensorData* lsData) {
	double vertical = lsData->voltTop - lsData->voltBottom;
	double horizontal = lsData->voltRight - lsData->voltLeft;
	if(abs(vertical)>tolerance || abs(horizontal)>tolerance) *inTolerance = false;
	else *inTolerance = true;
	return OK;
}

Status PositioningModule::LightSensorPositionCorrection(SpaData * sData, LightSensorData * lsData){
	double vertical = lsData->voltTop - lsData->voltBottom;
	double horizontal = lsData->voltRight - lsData->voltLeft;

	//TO-DO - find way to convert voltage into degree correction

	return OK;
}
