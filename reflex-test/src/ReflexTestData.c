/*
 * ReflexTestData.c
 *
 *  Created on: Jun 3, 2015
 *      Author: travis
 */

#include "ReflexTestData.h"

#include <stdio.h>
#include <stdlib.h>

static uint32_t sequence[REFLEXTESTDATA_SEQUENCE_LENGTH];
static int32_t index = 0;
static int32_t pressedButton = 0;
static double responseTime;
static ReflexTest_st currentState = init_st;
static double min = 5.0;
static double max = 0.0;
static double average = 0.0;
static double highScores[REFLEXTESTDATA_NUMBER_OF_HIGH_SCORES];

void ReflexTestData_Init() {
  index = 0;
  pressedButton = 0;
  responseTime = 0.0;
  min = 5.0;
  max = 0.0;
  average = 0.0;
  currentState = init_st;

  int i;
  for (i = 0; i < REFLEXTESTDATA_SEQUENCE_LENGTH; i++) {
    sequence[i] = 0;
  }
}

bool ReflexTestData_IsSequenceDone() {
  return (index == (REFLEXTESTDATA_SEQUENCE_LENGTH));
}

int32_t ReflexTestData_GetNextLed() {

  if (index < REFLEXTESTDATA_SEQUENCE_LENGTH) {
   return sequence[index];
  }
  else {
    return REFLEXTESTDATA_ERROR;
  }
}

void ReflexTestData_IncrementIndex() {
  // -1 so that index stays on the last element
  if (index < REFLEXTESTDATA_SEQUENCE_LENGTH-1) {
    index++;
  }
}

int32_t ReflexTestData_GetCurrentIndex() {
  return index;
}

void ReflexTestData_PrintSequence() {
  int i;
  printf("{");
  for (i = 0; i < REFLEXTESTDATA_SEQUENCE_LENGTH-1; i++) {
    printf("%lu, ", sequence[i]);
  }
  printf("%lu};\n", sequence[REFLEXTESTDATA_SEQUENCE_LENGTH-1]);
}

uint32_t* ReflexTestData_GenerateSequence(int32_t seed) {

  index = 0; //reset the global index whenever a new sequence is generated

  srand(seed); //initialize random number generator
  int i;
  for (i = 0; i < REFLEXTESTDATA_SEQUENCE_LENGTH; i++) {
    // Generate values between 1-4
    sequence[i] = (rand() % REFLEXTESTDATA_NUMBER_OF_LEDS) + 1;
  }

#ifdef REFLEXTESTDATA_DEBUG
  ReflexTestData_PrintSequence();
#endif

  return sequence;
}

int32_t ReflexTestData_GetPressedButton() {
  return pressedButton;
}

void ReflexTestData_SetPressedButton(int32_t value) {
  pressedButton = value;
}

void ReflexTestData_SetCurrentState(ReflexTest_st newState) {
  currentState = newState;
}

ReflexTest_st ReflexTestData_GetCurrentState() {
  return currentState;
}

bool ReflexTestData_IsCorrectButtonPressed() {
  return (pressedButton == sequence[index]);
}

void ReflexTestData_SetResponseTime(double inputTime) {
  responseTime = inputTime;
}

double ReflexTestData_GetResponseTime() {
  return responseTime;
}

void ReflexTestData_SetMinResponseTime(double responseTime) {
  min = responseTime;
}

double ReflexTestData_GetMinResponseTime() {
  return min;
}

void ReflexTestData_SetMaxResponseTime(double responseTime) {
  max = responseTime;
}

double ReflexTestData_GetMaxResponseTime() {
  return max;
}

void ReflexTestData_SetAverageResponseTime(double responseTime) {
  average = responseTime;
}

double ReflexTestData_GetAverageResponseTime() {
  return average;
}

double* ReflexTestData_GetHighScores() {
  return highScores;
}

int compare_function(const void *a,const void *b) {
  double *x = (double *) a;
  double *y = (double *) b;


  if (*x < *y) {
    return -1;
  }
  else if (*x > *y) {
    return 1;
  }

  return 0;
}

void ReflexTestData_UpdateScores() {

  if (highScores[REFLEXTESTDATA_NUMBER_OF_HIGH_SCORES-1] < average) {
    highScores[REFLEXTESTDATA_NUMBER_OF_HIGH_SCORES-1] = average;
    qsort(highScores, REFLEXTESTDATA_NUMBER_OF_HIGH_SCORES, sizeof(double), compare_function);
  }

}
