#include "Executor.h"
#include "ButtonConductor.h"
#include "LedConductor.h"
#include "TimerConductor.h"
#include "LcdConductor.h"

#define TICK_PERIOD       1                       // 1ms tick period
#define FIVE_SECOND_WAIT  (5000 / (TICK_PERIOD))  // 5000ms = 5s

void Executor_Init(void) {

  //call init on each of the conductors
  ButtonConductor_Init();
  LedConductor_Init();
  LcdConductor_Init();
  TimerConductor_Init();
}

bool Executor_Run(void) {

  //state actions first
  ButtonConductor_Run();
  LedConductor_Run();
  LcdConductor_Run();
  TimerConductor_Run();

  //state update next
  ReflexTestData_SetCurrentState(ReflexTest_tick_Function(ReflexTestData_GetCurrentState()));
  return true;
}

ReflexTest_st ReflexTest_tick_Function(ReflexTest_st currentState) {
  static uint32_t fiveSecondTimer = 0;

  // state actions
  switch (currentState) {
    case init_st:
      break;
    case show_info_st:
      break;
    case wait_five_seconds_st:
      fiveSecondTimer++;
      break;
    case wait_between_flash_st:
      break;
    case blink_led_st:
      break;
    case wait_for_button_st:
      break;
    case show_stats_st:
      break;
    case update_scores_st:
      break;
  }

   // state update
  switch (currentState) {
    case init_st:
      currentState = show_info_st;
      break;
    case show_info_st:
      currentState = wait_info_st;
      break;
    case wait_five_seconds_st:
      if (fiveSecondTimer > )
      break;
    case wait_between_flash_st:
      break;
    case blink_led_st:
      break;
    case wait_for_button_st:
      break;
    case show_stats_st:
      break;
    case update_scores_st:
      break;
  }

  return currentState;
}
