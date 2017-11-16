/*
 * SPACalculation.h
 *
 *  This program calculate the sun position with Solar Position Algorithm
 *  by Ibrahim Reda and Afshin Andreas.
 *
 *  Created on: Nov 14, 2017
 *      Author: Allen
 */

#ifndef SPACALCULATION_H_
#define SPACALCULATION_H_

#include "SystemStructs.h"
#include "Globals.h"
#ifdef DEBUG
#include "Debug.h"
#endif
extern "C" {
  #include "spa.h" //include the SPA header file
}


//Update period of the solar tracker
#define UPDATE_PEIORD 1800

//2017 constants
#define DELTA_UT1 0.3
#define DELTA_T 69.1

//Pitt Benedum Hall constant
#define TIMEZONE -4 // Pittsburgh
#define LONGITUDE -79.958767 // Pitt Benedum Hall
#define LATITUDE 40.443651 // Pitt Benedum Hall
#define HEIGHT 40 // Pitt Benedum Hall

  //declare the SPA structure


class SPACalculation{
	private:
		spa_data spa;
		int result; // SPA result
		
		float lo = LONGITUDE;
		float la = LATITUDE;
		float hei = HEIGHT;
#ifdef DEBUG
		Debug debug;
#endif
	public:
		SPACalculation();
		~SPACalculation();
		Status GetSpaData(const GPSData* gData, SpaData* sData);
};


#endif /* SPACALCULATION_H_ */
