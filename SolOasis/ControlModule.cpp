#include "ControlModule.h"
#include "Ports.h"
#include <Arduino.h>
#include <Servo.h>

Servo horizontalServo;
Servo verticalServo;

ControlModule::ControlModule(){
	horizontalServo.attach(RotMotorPin);
	verticalServo.attach(TiltMotorPin);
	digitalWrite(RotRBSw1Pin, LOW);
	digitalWrite(RotRBSw1Pin, LOW);
}

ControlModule::~ControlModule(){
  
}

Status ControlModule::rotateMotors(int AzimuthDgr, int ElevationDgr){
	if (AzimuthDgr < 0 || AzimuthDgr > 360)
		return MOTRO_DGR_INVALID;
	if (ElevationDgr < 0 || ElevationDgr > 90)
		return MOTRO_DGR_INVALID;
	if (AzimuthDgr > 180){
		AzimuthDgr = AzimuthDgr - 180;
		ElevationDgr = - (ElevationDgr - 180);
	}

	if (rotateHorizontal(AzimuthDgr) &&	rotateVertical(ElevationDgr))
		return OK;

}

Status ControlModule::rotateHorizontal(int dgr){
	if (dgr < 0 || dgr > 180)
		return MOTRO_DGR_INVALID;
	digitalWrite(RotRBSw1Pin, HIGH);
	horizontalServo.write(dgr);
	digitalWrite(RotRBSw1Pin, LOW);
	return OK;
}

Status ControlModule::rotateVertical(int dgr){
	if (dgr < 0 || dgr > 180)
		return MOTRO_DGR_INVALID;
	digitalWrite(TiltRBSw1Pin, HIGH);
	verticalServo.write(dgr);
	digitalWrite(RotRBSw1Pin, LOW);
	return OK;
}

