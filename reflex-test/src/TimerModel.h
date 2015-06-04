/*
 * TimerModel.h
 *
 *  Created on: Jun 3, 2015
 *      Author: travis
 */

#ifndef TIMERMODEL_H_
#define TIMERMODEL_H_

#include "ReflexTestData.h"

void TimerModel_Init(void);

/**
 * Called by the Conductor to get the current state from ReflexTestData
 * @return  returns the current state
 */
ReflexTest_st TimerModel_GetCurrentState(void);

/**
 * Sets the most recent response time in ReflexTestData to the parameter.
 * @param responseTime The response time value to save.
 */
void TimerModel_SetResponseTime(double responseTime);

#endif /* TIMERMODEL_H_ */
