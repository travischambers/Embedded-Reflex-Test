#ifndef LEDMODEL_H_
#define LEDMODEL_H_

#include "ReflexTestData.h"
#include <stdint.h>

/**
 * Initialization function for the LED Model.
 */
void LedModel_Init();

/**
 * Returns the LED to flash in the sequence.
 * @return The number of the LED to flash next.
 */
int32_t LedModel_GetLed();

/**
 * Increments the Index of the ReflexTestData.
 */
void LedModel_IncrementIndex();

/**
 * Called by the Conductor to get the current state from ReflexTestData
 * @return  returns the current state
 */
ReflexTest_st LedModel_GetCurrentState(void);

#endif /* LEDMODEL_H_ */
