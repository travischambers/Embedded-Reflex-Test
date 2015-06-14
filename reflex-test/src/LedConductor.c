#include "LedConductor.h"
#include "LedModel.h"
#include "LedHardware.h"
#include "intervalTimer.h"
#include <stdint.h>

void LedConductor_Init() {
  LedModel_Init();
  LedHardware_Init();
}

void LedConductor_Run() {

  int32_t flashedLed = 0;
  // state actions
  switch (LedModel_GetCurrentState()) {
    case init_st:
      break;
    case show_info_st:
      // Turn off all of the LEDs at the begninning of each round.
      LedHardware_BlankAllLeds();
      break;
    case wait_info_st:
      // Turn off all of the LEDs at the begninning of each round.
      LedHardware_BlankAllLeds();
      break;
    case wait_five_seconds_st:
      break;
    case blank_screen_st:
      break;
    case wait_between_flash_st:
      break;
    case blink_led_st:
      // Get the current LED in the sequence and turn it on.
      flashedLed = LedModel_GetLed();
      LedHardware_Enable(flashedLed);
      break;
    case wait_for_button_st:
      break;
    case button_pressed_st:
      // Increment the index, then turn off the LEDs.
      LedModel_IncrementIndex();
      LedHardware_BlankAllLeds();
      break;
    case show_stats_st:
      break;
    case wait_stats_st:
      break;
    case update_scores_st:
      break;
  }
}
