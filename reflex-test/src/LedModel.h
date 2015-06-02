/*
 * LedModel.h
 *
 *  Created on: Jun 1, 2015
 *      Author: travis
 */

#ifndef LEDMODEL_H_
#define LEDMODEL_H_

#include <stdint.h>

// Uncomment the line below to enable debug output.
#define LEDMODEL_DEBUG

#define LEDMODEL_SEQUENCE_LENGTH 10
#define LEDMODEL_NUMBER_OF_LEDS 4

void LedModel_Init(void);

uint32_t* LedModel_generateSequence(int32_t seed);

#endif /* LEDMODEL_H_ */
