#include "ControlModule.h"
#include <Arduino.h>
#include <Servo.h>
#include "SystemStructs.h"
#include "Globals.h"
Servo horizontalServo;
Servo verticalServo;

ControlModule::ControlModule(){
	horizontalServo.attach(RotMotorPin);
	verticalServo.attach(TiltMotorPin);
	digitalWrite(RotRBSw1Pin, LOW);
	digitalWrite(TiltRBSw1Pin, LOW);
	lastHorizontalDgr = 0;
    lastVerticalDgr = 0;
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
#if defined(DEBUG) && defined(DEBUG_CONT)
	debug.print("Servo:");debug.print(AzimuthDgr);debug.print(" / ");debug.println(ElevationDgr);
#endif
	if (rotateHorizontal(AzimuthDgr) != OK)
		return MOTRO_MOVE_HORIZONTAL_ERROR;
	else if (rotateVertical(ElevationDgr) != OK)
		return MOTRO_MOVE_VERTICAL_ERROR;
	else {
		return OK;
	}

}

Status ControlModule::rotateHorizontal(int dgr){
	if (dgr < 0 || dgr > 180)
		return MOTRO_DGR_INVALID;
	digitalWrite(RotRBSw1Pin, HIGH);
	horizontalServo.write(dgr);
	delay((int)(SERVO_DELAY_TIME + abs(lastHorizontalDgr - dgr) * SERVO_DELAY_RATIO));
#if defined(DEBUG) && defined(DEBUG_CONT)
	debug.print("    >delay: ");debug.println((int)(SERVO_DELAY_TIME + abs(lastHorizontalDgr - dgr) * SERVO_DELAY_RATIO));
#endif
	digitalWrite(RotRBSw1Pin, LOW);
	lastHorizontalDgr = dgr;
	return OK;
}

Status ControlModule::rotateVertical(int dgr){
	if (dgr < 0 || dgr > 180)
		return MOTRO_DGR_INVALID;
	digitalWrite(TiltRBSw1Pin, HIGH);
	verticalServo.write(dgr);
	delay((int)(SERVO_DELAY_TIME + abs(lastVerticalDgr - dgr) * SERVO_DELAY_RATIO));
	digitalWrite(TiltRBSw1Pin, LOW);
	lastVerticalDgr = dgr;
	return OK;
}

