/*
 * PositioningIntfc.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#ifndef _POSITIONING_INTFC_H_
#define _POSITIONING_INTFC_H_

#include "Globals.h"
#include "SystemStructs.h"

class PositioningIntfc{
private:

public:
	virtual ~PositioningIntfc(){};
	virtual Status GetSPAData(GPSData *gData, SpaData * sData) = 0;
	virtual Status LightSensorsInTolerance(bool * inTolerance, LightSensorData * lsData) = 0;
	virtual Status LightSensorPositionCorrection(SpaData * sData, LightSensorData * lsData) = 0;
};

#endif /* _POSITIONING_INTFC_H_ */
