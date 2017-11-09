/*
 * Logger.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "Globals.h"
#include "SystemStructs.h"

#ifdef DEBUG
#include "Debug.h"
#endif

class Logger{
private:
#ifdef DEBUG
	Debug debug;
#endif

public:
	Logger();
	~Logger();
};

#endif /* LOGGER_H_ */
