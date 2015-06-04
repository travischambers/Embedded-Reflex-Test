/*
 * LedConductor.c
 *
 *  Created on: Jun 1, 2015
 *      Author: travis
 */

#include "LedConductor.h"
#include "LedModel.h"
#include "LedHardware.h"
#include "intervalTimer.h"

void LedConductor_Init() {

  LedModel_Init();
  LedHardware_Init();
}

void LedConductor_Run() {
  // state actions
  switch (LedModel_GetCurrentState()) {
    case init_st:
      break;
    case show_info_st:
      break;
    case wait_info_st:
      break;
    case wait_five_seconds_st:
      break;
    case blank_screen_st:
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
      break;
    case wait_stats_st:
      break;
    case update_scores_st:
      break;
  }
}
