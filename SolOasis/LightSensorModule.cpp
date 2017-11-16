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


Status LightSensorModule::GetLightSensorData(LightSensorData * lightSensorData) {
  double voltTopLeft = analogRead(PRTopLeftPin);
  double voltTopRight = analogRead(PRTopRightPin);
  double voltBottomLeft = analogRead(PRBottomLeftPin);
  double voltBottomRight = analogRead(PRBottomRightPin);
  lightSensorData->voltTop = (voltTopLeft + voltTopRight) / 2;
  lightSensorData->voltBottom = (voltBottomLeft + voltBottomRight) / 2;
  lightSensorData->voltLeft = (voltTopLeft + voltBottomLeft) / 2;
  lightSensorData->voltRight = (voltTopRight + voltBottomRight) / 2;
  return OK;
}

