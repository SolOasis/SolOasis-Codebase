/*
 * DiagnosticsModule.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Chris
 */

#ifndef _DIAGNOSTICS_MODULE_H_
#define _DIAGNOSTICS_MODULE_H_

#include "Globals.h"
#include "SystemStructs.h"
#include "Ports.h"

#ifdef DEBUG
#include "Debug.h"
#endif

class DiagnosticsModule{
private:
#ifdef DEBUG
	Debug debug;
#endif

public:
	DiagnosticsModule();
	~DiagnosticsModule();
};

#endif /* _DIAGNOSTICS_MODULE_H_ */
