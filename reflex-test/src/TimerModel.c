#include "TimerModel.h"
#include <stdio.h>

#define MAX_INITIAL_VALUE 5.000 //initialized to slowest possible time
#define MIN_INITIAL_VALUE 0.000 //initialized to fastest possible time

// Global variables used to store information about the current round.
static double min = MAX_INITIAL_VALUE;
static double max = MIN_INITIAL_VALUE;
static double average = MAX_INITIAL_VALUE;
static double times[REFLEXTESTDATA_SEQUENCE_LENGTH];

void TimerModel_Init() {
  // Initialize all of the global variables.
  min = MAX_INITIAL_VALUE;
  max = MIN_INITIAL_VALUE;
  average = MAX_INITIAL_VALUE;
  int i;
  for (i = 0; i < REFLEXTESTDATA_SEQUENCE_LENGTH; i++) {
    times[i] = 0.0;
  }
}

ReflexTest_st TimerModel_GetCurrentState() {
  return ReflexTestData_GetCurrentState();
}

/**
 * Helper function to show the contents of the response time array
 */
void TimerModel_printStatsArray() {
  int i;
  printf("{");
  for (i = 0; i < REFLEXTESTDATA_SEQUENCE_LENGTH-1; i++) {
    printf("%lf, ", times[i]);
  }
  printf("%lf}\n", times[REFLEXTESTDATA_SEQUENCE_LENGTH-1]);
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

  ReflexTestData_SetMinResponseTime(min);
  ReflexTestData_SetMaxResponseTime(max);
  ReflexTestData_SetAverageResponseTime(average);
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
  //save it to the shared, global model
  TimerModel_SetMostRecentResponseTime(responseTime);
}

void TimerModel_SetMostRecentResponseTime(double responseTime) {
  ReflexTestData_SetResponseTime(responseTime);
}
