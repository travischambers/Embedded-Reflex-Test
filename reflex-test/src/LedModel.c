/*
 * LedModel.c
 *
 *  Created on: Jun 1, 2015
 *      Author: travis
 */

#include "LedModel.h"
#include <stdlib.h>
#include <stdio.h>
static uint32_t sequence[LEDMODEL_SEQUENCE_LENGTH];

void LedModel_Init() {

}


void LedModel_printSequence() {
  int i;
  printf("{");
  for (i = 0; i < LEDMODEL_SEQUENCE_LENGTH-1; i++) {
    printf("%lu, ", sequence[i]);
  }
  printf("%lu};\n", sequence[LEDMODEL_SEQUENCE_LENGTH-1]);
}

uint32_t* LedModel_generateSequence(int32_t seed) {

  srand(seed); //initialize random number generator
  int i;
  for (i = 0; i < LEDMODEL_SEQUENCE_LENGTH; i++) {
    sequence[i] = rand() % LEDMODEL_NUMBER_OF_LEDS;
  }

#ifdef LEDMODEL_DEBUG
  LedModel_printSequence();
#endif

  return sequence;
}
