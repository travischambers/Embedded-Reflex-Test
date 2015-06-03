/*
 * LedModel.h
 *
 *  Created on: Jun 1, 2015
 *      Author: travis
 */

#ifndef LEDMODEL_H_
#define LEDMODEL_H_

#include <stdint.h>
#include <stdbool.h>

void LedModel_Init();
int32_t LedModel_GetNextLed();
bool LedModel_IsSequenceDone(void);

#endif /* LEDMODEL_H_ */


