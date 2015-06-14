#include "TimerConductor.h"
#include "TimerHardware.h"
#include "TimerModel.h"

void TimerConductor_Init() {
  TimerHardware_Init();
  TimerModel_Init();
}

void TimerConductor_Run() {
  double responseTime;
  // state actions
  switch (TimerModel_GetCurrentState()) {
    case init_st:
      break;
    case show_info_st:
      // Start the timer when the info is printed. This is then stopped when
      // The user pushes a button and the value is used to seed our random
      // generator.
      TimerHardware_ResetTimer();
      TimerHardware_StartTimer();
      break;
    case wait_info_st:
      break;
    case wait_five_seconds_st:
      break;
    case blank_screen_st:
      // Stop the timer, and set the most recent response time.
      TimerHardware_StopTimer();
      responseTime = TimerHardware_GetResponseTime();
      TimerModel_SetMostRecentResponseTime(responseTime);

      // Clear the old stats in preparation for a new round.
      TimerModel_ClearOldStats();
      break;
    case wait_between_flash_st:
      break;
    case blink_led_st:
      // Start the timer when an LED is enabled. This is stopped once the user
      // pushes the correct button.
      TimerHardware_ResetTimer();
      TimerHardware_StartTimer();
      break;
    case wait_for_button_st:
      break;
    case button_pressed_st:
      TimerHardware_StopTimer();
      responseTime = TimerHardware_GetResponseTime();
      TimerModel_SetMostRecentResponseTime(responseTime);
      TimerModel_RecordResponseTime(responseTime);
      break;
    case show_stats_st:
      TimerModel_CalculateStats();
      break;
    case wait_stats_st:
      break;
    case update_scores_st:
      break;
  }
}
