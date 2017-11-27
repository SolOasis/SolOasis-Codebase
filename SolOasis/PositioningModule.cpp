/*
 * PositioningModule.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: Chris
 */

#include "PositioningModule.h"

PositioningModule::PositioningModule() {
}

PositioningModule::~PositioningModule() {
}

Status PositioningModule::GetSPAData(GPSData * gData, SpaData* sData) {
	return spaCalc.GetSpaData(gData,sData);
}
