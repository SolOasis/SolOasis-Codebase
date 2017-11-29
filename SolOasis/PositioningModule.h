/*
 * PositioningModule.h
 *
 *  Created on: Nov 24, 2017
 *      Author: Chris
 */

#ifndef _POSITIONING_MODULE_H_
#define _POSITIONING_MODULE_H_

#include "PositioningIntfc.h"
#include "SPACalculation.h"

class PositioningModule : public PositioningIntfc{
private:
	SPACalculation spaCalc;
public:
	PositioningModule();
	~PositioningModule();
	Status GetSPAData(GPSData * gData, SpaData *sData);
	Status LightSensorsInTolerance(bool * inTolerance, LightSensorData * lsData);
	Status HorizontalDegCorrection(double * deg);
	Status VerticalDegCorrection(double * deg);
};

#endif /* _POSITIONING_MODULE_H_ */
