/*
 * TimerConductor.c
 *
 *  Created on: Jun 3, 2015
 *      Author: travis
 */

#include "TimerConductor.h"
#include "TimerHardware.h"
#include "TimerModel.h"

void TimerConductor_Init() {
  TimerHardware_Init();
  TimerModel_Init();
}

void TimerConductor_Run() {
  // state actions
  switch (TimerModel_GetCurrentState()) {
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
