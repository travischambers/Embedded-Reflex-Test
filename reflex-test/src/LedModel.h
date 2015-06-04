/*
 * LedModel.h
 *
 *  Created on: Jun 1, 2015
 *      Author: travis
 */

#ifndef LEDMODEL_H_
#define LEDMODEL_H_

#include "ReflexTestData.h"
#include <stdint.h>
#include <stdbool.h>

void LedModel_Init();
int32_t LedModel_GetNextLed();
bool LedModel_IsSequenceDone(void);

/**
 * Called by the Conductor to get the current state from ReflexTestData
 * @return  returns the current state
 */
reflexTest_st LedModel_GetCurrentState(void);

#endif /* LEDMODEL_H_ */
