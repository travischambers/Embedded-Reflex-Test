/*
 * LcdModel.c
 *
 *  Created on: Jun 3, 2015
 *      Author: travis
 */

#include "LcdModel.h"

void LcdModel_Init() {

}

ReflexTest_st LcdModel_GetCurrentState() {
  return ReflexTestData_GetCurrentState();
}

double LcdModel_GetAverageResponseTime() {
  return ReflexTestData_GetAverageResponseTime();
}

double LcdModel_GetMinResponseTime() {
  return ReflexTestData_GetMinResponseTime();
}

double LcdModel_GetMaxResponseTime() {
  return ReflexTestData_GetMaxResponseTime();
}
