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

/**
 * Deletes all te stats from the previous run to be ready for the new round.
 */
void TimerModel_ClearOldStats();

/**
 * Calculates the MIN, MAX, and AVERAGE for this run of the reflex test.
 */
void TimerModel_CalculateStats();

/**
 * Returns the minimum response time of the round.
 * @return The minimum response time of the round.
 */
double TimerModel_GetMin();

/**
 * Returns the maximum response time of the round.
 * @return The maximum response time of the round.
 */
double TimerModel_GetMax();

/**
 * Returns the average response time of the round.
 * @return The average response time of the round.
 */
double TimerModel_GetAverage();

#endif /* TIMERMODEL_H_ */
