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
	return OK;
}

Status PositioningModule::HorizontalDegCorrection(double* deg) {
	return OK;
}

Status PositioningModule::VerticalDegCorrection(double* deg) {
	return OK;
}
