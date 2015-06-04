/*
 * LedModel.c
 *
 *  Created on: Jun 1, 2015
 *      Author: travis
 */

#include "LedModel.h"
#include <stdlib.h>
#include <stdio.h>

void LedModel_Init() {

}

int32_t LedModel_GetNextLedAndIncrement() {
  return ReflexTestData_GetNextLedAndIncrement();
}

bool LedModel_IsSequenceDone() {
  return ReflexTestData_IsSequenceDone();
}

ReflexTest_st LedModel_GetCurrentState() {
  return ReflexTestData_GetCurrentState();
}
