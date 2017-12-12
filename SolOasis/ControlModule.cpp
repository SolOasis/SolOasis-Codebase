/*
 * ControlModule.cpp
 *
 *  Created on: Nov 9, 2017
 *      Author: Allen
 */

#include "ControlModule.h"
#include <Arduino.h>
#include <Servo.h>
#include "SystemStructs.h"
#include "Globals.h"
Servo horizontalServo;
Servo verticalServo;

//**************************************************************************************
// ~Control Module Constructor~
//**************************************************************************************
ControlModule::ControlModule(){
    // Attach servos to correct pins
	horizontalServo.attach(RotMotorPin);
	verticalServo.attach(TiltMotorPin);

    // Disable servo to prevent energy draw
	digitalWrite(RotRBSw1Pin, LOW);
	digitalWrite(TiltRBSw1Pin, LOW);

	//TEST ONLY
//	digitalWrite(RotRBSw1Pin, HIGH);
//	digitalWrite(TiltRBSw1Pin, HIGH);

    // Initiate the record
	lastHorizontalDgr = 0;
    lastVerticalDgr = 0;
}
//**************************************************************************************


//**************************************************************************************
// ~Control Module Destructor~
//**************************************************************************************
ControlModule::~ControlModule(){

}
//**************************************************************************************


//**************************************************************************************
// ~Rotate Motors~
// Takes in horizontal and vertical degree values and alters them to useable data,
// then calls private functions to rotate servos on each axis
//**************************************************************************************
Status ControlModule::rotateMotors(int AzimuthDgr, int ElevationDgr){
    // Check if the inputs are valid
	if (AzimuthDgr < 0 || AzimuthDgr > 360)
		return MOTOR_DGR_INVALID;
	if (ElevationDgr < 0 || ElevationDgr > 180)
		return MOTOR_DGR_INVALID;
    // Transformation for the two servo when the degree is more than 180
    // since the servo could only move from 0 to 180
//	if (AzimuthDgr > 180){
//		AzimuthDgr = AzimuthDgr - 180;
//		ElevationDgr = - (ElevationDgr - 180);
//	}
#if defined(DEBUG) && defined(DEBUG_CONT)
	debug.print("Servo:");debug.print(AzimuthDgr);debug.print(" / ");debug.println(ElevationDgr);
#endif

    // Rotate servo motors
	if (rotateHorizontal(AzimuthDgr) != OK)
		return MOTOR_MOVE_HORIZONTAL_ERROR;
	delay(500);
	if (rotateVertical(ElevationDgr) != OK)
		return MOTOR_MOVE_VERTICAL_ERROR;

    // Wait until the servos are in correct position, turn them off and record the position
    waitMovementAndRecord(AzimuthDgr, ElevationDgr);

	return OK;

}
//**************************************************************************************


//**************************************************************************************
// ~Break Motors~
// Turns regenerative break on or off
//**************************************************************************************
void ControlModule::breakMotors(bool hor, bool ver) {
    if (hor)
	    digitalWrite(RotRBSw1Pin, LOW);
    if (ver)
	    digitalWrite(TiltRBSw1Pin, LOW);
}
//**************************************************************************************


//**************************************************************************************
// ~Wait For Movement And Record Values~
// Allows servo movement and records last degree values for future use
//**************************************************************************************
void ControlModule::waitMovementAndRecord(int AzimuthDgr, int ElevationDgr) {
    // Wait rotation
    int dgrDiff = (abs(lastHorizontalDgr - AzimuthDgr) > abs(lastVerticalDgr - ElevationDgr)) ? abs(lastHorizontalDgr - AzimuthDgr) : abs(lastVerticalDgr - ElevationDgr);
	int delayTime = (int)(SERVO_DELAY_TIME + dgrDiff * SERVO_DELAY_RATIO);
#ifdef defined(DEBUG) && defined(DEBUG_CONT)
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
//**************************************************************************************
        

//**************************************************************************************
// ~Rotate Horizontal Servos~
//**************************************************************************************
Status ControlModule::rotateHorizontal(int dgr){
	if (dgr < 0 || dgr > 180)
		return MOTOR_DGR_INVALID;
	digitalWrite(RotRBSw1Pin, HIGH);
	horizontalServo.write(dgr);

	return OK;
}
//**************************************************************************************


//**************************************************************************************
// ~Rotate Vertical Servos~
//**************************************************************************************
Status ControlModule::rotateVertical(int dgr){
	if (dgr < 0 || dgr > 180)
		return MOTOR_DGR_INVALID;
	digitalWrite(TiltRBSw1Pin, HIGH);
	verticalServo.write(dgr);

	return OK;
}
//**************************************************************************************
