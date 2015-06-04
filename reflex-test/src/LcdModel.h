/*
 * LcdModel.h
 *
 *  Created on: Jun 3, 2015
 *      Author: travis
 */

#ifndef LCDMODEL_H_
#define LCDMODEL_H_

#include "ReflexTestData.h"

void LcdModel_Init(void);

/**
 * Called by the Conductor to get the current state from ReflexTestData
 * @return  returns the current state
 */
reflexTest_st LcdModel_GetCurrentState(void);

#endif /* LCDMODEL_H_ */
