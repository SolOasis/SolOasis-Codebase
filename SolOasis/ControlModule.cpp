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
#ifdef DEBUG
	debug.print("Servo:");debug.print(AzimuthDgr);debug.print(" / ");debug.println(ElevationDgr);
#endif

    // Rotate motors
	if (rotateHorizontal(AzimuthDgr) != OK)
		return MOTRO_MOVE_HORIZONTAL_ERROR;
	if (rotateVertical(ElevationDgr) != OK)
		return MOTRO_MOVE_VERTICAL_ERROR;

    waitMovementAndRecord(AzimuthDgr, ElevationDgr);

	return OK;

}

void ControlModule::breakMotors(bool hor, bool ver) {
    if (hor) 
	    digitalWrite(RotRBSw1Pin, LOW);
    if (ver)
	    digitalWrite(TiltRBSw1Pin, LOW);
}

void ControlModule::waitMovementAndRecord(int AzimuthDgr, int ElevationDgr) {
    // Wait rotation
    int dgrDiff = (abs(lastHorizontalDgr - AzimuthDgr) > abs(lastVerticalDgr - ElevationDgr)) ? abs(lastHorizontalDgr - AzimuthDgr) : abs(lastVerticalDgr - ElevationDgr);
	int delayTime = (int)(SERVO_DELAY_TIME + dgrDiff * SERVO_DELAY_RATIO);
#ifdef DEBUG
	debug.print("Wait delayTime :");debug.println(delayTime);
#endif
    delay(delayTime);
    // Break the motor
    breakMotors(true, true);
    //Record the degree
    lastHorizontalDgr = AzimuthDgr;
    lastVerticalDgr = ElevationDgr;
    delay(500);
}
        
Status ControlModule::rotateHorizontal(int dgr){
	if (dgr < 0 || dgr > 180)
		return MOTRO_DGR_INVALID;
	digitalWrite(RotRBSw1Pin, HIGH);
	horizontalServo.write(dgr);
	return OK;
}

Status ControlModule::rotateVertical(int dgr){
	if (dgr < 0 || dgr > 180)
		return MOTRO_DGR_INVALID;
	digitalWrite(TiltRBSw1Pin, HIGH);
	verticalServo.write(dgr);
	return OK;
}

