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

//state machine
enum reflexTest_st {
  init_st,               // init state
  show_info_st,          // display instructions on the lcd
  wait_five_seconds_st,  // wait_five_seconds before blinking an led
  blink_led_st,          // blink an led
  wait_for_button_st,    // wait for the user to press a button
  wait_between_flash_st, // wait one second
  show_stats_st,         // show user's fastest, slowest, and average time
  update_scores_st,      // compute average and rank score
};

void ReflexTestData_SetCurrentState(reflexTest_st newState);
reflexTest_st ReflexTestData_GetCurrentState(void);



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
