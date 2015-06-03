/*
 * ReflexTestData.h
 *
 *  Created on: Jun 3, 2015
 *      Author: travis
 */

#ifndef REFLEXTESTDATA_H_
#define REFLEXTESTDATA_H_

#include <stdint.h>
#include <stdbool.h>

// Uncomment the line below to enable debug output.
//#define LEDMODEL_DEBUG

#define LEDMODEL_ERROR -1
#define LEDMODEL_SEQUENCE_LENGTH 10
#define LEDMODEL_NUMBER_OF_LEDS 4

void ReflexTestData_Init(void);

uint32_t* ReflexTestData_GenerateSequence(int32_t seed);

//led model methods
int32_t ReflexTestData_GetNextLed(void);
bool ReflexTestData_IsSequenceDone(void);

//button model methods
int32_t ReflexTestData_GetPressedButton(void);
void ReflexTestData_SetPressedButton(int32_t value);

//timer model methods
double ReflexTestData_GetResponseTime(void);

#endif /* REFLEXTESTDATA_H_ */
