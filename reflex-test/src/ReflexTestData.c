/*
 * ReflexTestData.c
 *
 *  Created on: Jun 3, 2015
 *      Author: travis
 */

#include "ReflexTestData.h"

#include <stdio.h>
#include <stdlib.h>

static uint32_t sequence[LEDMODEL_SEQUENCE_LENGTH];
static int32_t index = 0;
static int32_t pressedButton = 0;
static double responseTime;
static ReflexTest_st currentState = init_st;

bool ReflexTestData_IsSequenceDone() {
  return (index == (LEDMODEL_SEQUENCE_LENGTH));
}

int32_t ReflexTestData_GetNextLed() {

  if (index < LEDMODEL_SEQUENCE_LENGTH) {
   return sequence[index++];
  }
  else {
    return LEDMODEL_ERROR;
  }
}

i

void ReflexTestData_printSequence() {
  int i;
  printf("{");
  for (i = 0; i < LEDMODEL_SEQUENCE_LENGTH-1; i++) {
    printf("%lu, ", sequence[i]);
  }
  printf("%lu};\n", sequence[LEDMODEL_SEQUENCE_LENGTH-1]);
}

uint32_t* ReflexTestData_GenerateSequence(int32_t seed) {

  index = 0; //reset the global index whenever a new sequence is generated

  srand(seed); //initialize random number generator
  int i;
  for (i = 0; i < LEDMODEL_SEQUENCE_LENGTH; i++) {
    sequence[i] = rand() % LEDMODEL_NUMBER_OF_LEDS;
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
