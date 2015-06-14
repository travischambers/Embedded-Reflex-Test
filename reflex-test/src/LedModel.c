#include "LedModel.h"
#include <stdlib.h>
#include <stdio.h>

void LedModel_Init() {

}

int32_t LedModel_GetLed() {
  return ReflexTestData_GetLed();
}

void LedModel_IncrementIndex() {
  ReflexTestData_IncrementIndex();
}

bool LedModel_IsSequenceDone() {
  return ReflexTestData_IsSequenceDone();
}

ReflexTest_st LedModel_GetCurrentState() {
  return ReflexTestData_GetCurrentState();
}
