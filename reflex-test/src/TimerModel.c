/*
 * TimerModel.c
 *
 *  Created on: Jun 3, 2015
 *      Author: travis
 */

#include "TimerModel.h"

#define MAX_INITIAL_VALUE 5.000 //initialized to slowest possible time
#define MIN_INITIAL_VALUE 0.000 //initialized to fastest possible time
static double min = MAX_INITIAL_VALUE;
static double max = MIN_INITIAL_VALUE;
static double average = MAX_INITIAL_VALUE;
static double times[REFLEXTESTDATA_SEQUENCE_LENGTH];

void TimerModel_Init() {

}

ReflexTest_st TimerModel_GetCurrentState() {
  return ReflexTestData_GetCurrentState();
}

void TimerModel_ClearOldStats() {
  min = MAX_INITIAL_VALUE;
  max = MIN_INITIAL_VALUE;
  average = MAX_INITIAL_VALUE;
  int i;
  for (i = 0; i < REFLEXTESTDATA_SEQUENCE_LENGTH; i++) {
    times[i] = MAX_INITIAL_VALUE;
  }
}

void TimerModel_CalculateStats() {
  int i;
  double runningTotal = 0;
  for (i = 0; i < REFLEXTESTDATA_SEQUENCE_LENGTH; i++) {
    if (times[i] > max) {
      max = times[i];
    }
    if (times[i] < min) {
      min = times[i];
    }
    runningTotal += times[i];
  }
  average = runningTotal/REFLEXTESTDATA_SEQUENCE_LENGTH;
}

double TimerModel_GetMin() {
  return min;
}

double TimerModel_GetMax() {
  return max;
}

double TimerModel_GetAverage() {
  return average;
}

void TimerModel_RecordResponseTime(double responseTime) {
  int32_t index = ReflexTestData_GetCurrentIndex();

  if (index < REFLEXTESTDATA_SEQUENCE_LENGTH) {
    times[index] = responseTime;
  }

  TimerModel_SetMostRecentResponseTime(responseTime); //save it to the shared model
}

void TimerModel_SetMostRecentResponseTime(double responseTime) {
  ReflexTestData_SetResponseTime(responseTime);
}
