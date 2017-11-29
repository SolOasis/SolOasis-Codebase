/*
 * LightSensorModule.cpp
 *
 *  Created on: Nov 9, 2017
 *      Author: Allen, Chris
 */

#include "LightSensorModule.h"

//#define PRTopPin A2
//#define PRBottomPin A3
//#define PRLeftPin A4
//#define PRRightPin A5
LightSensorModule::LightSensorModule() {
}

LightSensorModule::~LightSensorModule() {
}


Status LightSensorModule::GetLightSensorData(LightSensorData * lsData) {
  double voltTopLeft = analogRead(PRTopLeftPin);
  double voltTopRight = analogRead(PRTopRightPin);
  double voltBottomLeft = analogRead(PRBottomLeftPin);
  double voltBottomRight = analogRead(PRBottomRightPin);
  lsData->voltTop = (voltTopLeft + voltTopRight) / 2;
  lsData->voltBottom = (voltBottomLeft + voltBottomRight) / 2;
  lsData->voltLeft = (voltTopLeft + voltBottomLeft) / 2;
  lsData->voltRight = (voltTopRight + voltBottomRight) / 2;
  return OK;
}
