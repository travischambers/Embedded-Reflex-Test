/*
 * LcdConductor.c
 *
 *  Created on: Jun 3, 2015
 *      Author: travis
 */

#include "LcdConductor.h"
#include "LcdHardware.h"
#include "LcdModel.h"

void LcdConductor_Init() {
  LcdModel_Init();
  LcdHardware_Init();
}

void LcdConductor_Run() {
  double average, min, max;
  double* scores;
  // state actions
  switch (LcdModel_GetCurrentState()) {
    case init_st:
      break;
    case show_info_st:
      scores = LcdModel_GetHighScores();
      LcdHardware_ShowInfo(scores, REFLEXTESTDATA_NUMBER_OF_HIGH_SCORES);
      break;
    case wait_info_st:
      break;
    case wait_five_seconds_st:
      break;
    case blank_screen_st:
      LcdHardware_BlankScreen();
      break;
    case wait_between_flash_st:
      break;
    case blink_led_st:
      break;
    case wait_for_button_st:
      break;
    case button_pressed_st:
      break;
    case show_stats_st:
      average = LcdModel_GetAverageResponseTime();
      min = LcdModel_GetMinResponseTime();
      max = LcdModel_GetMaxResponseTime();
      LcdHardware_ShowStats(average, min, max);
      break;
    case wait_stats_st:
      break;
    case update_scores_st:
      LcdHardware_BlankScreen();
      break;
  }
}
