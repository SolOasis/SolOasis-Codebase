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
	static const int tolerance = 0.15;
	SPACalculation spaCalc;
public:
	PositioningModule();
	~PositioningModule();
	Status GetSPAData(GPSData * gData, SpaData *sData);
	Status LightSensorsInTolerance(bool * inTolerance, LightSensorData * lsData);
	Status LightSensorPositionCorrection(SpaData * sData, LightSensorData * lsData);
};

#endif /* _POSITIONING_MODULE_H_ */
