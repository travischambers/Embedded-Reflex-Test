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

#endif /* TIMERMODEL_H_ */
