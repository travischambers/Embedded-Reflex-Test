#include "Executor.h"
#include "ButtonConductor.h"
#include "LedConductor.h"
#include "TimerConductor.h"
#include "LcdConductor.h"
#include <stdlib.h>

#define TICK_PERIOD       1                       // 1ms tick period
#define FIVE_SECOND_WAIT  (5000 / (TICK_PERIOD))  // 5000ms = 5s
#define TWO_SECOND_WAIT   (2000 / (TICK_PERIOD))
#define ONE_SECOND_WAIT   (1000 / (TICK_PERIOD))

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
  ReflexTest_st nextState = ReflexTest_tick_Function(ReflexTestData_GetCurrentState());
  ReflexTestData_SetCurrentState(nextState);
  return true;
}

ReflexTest_st ReflexTest_tick_Function(ReflexTest_st currentState) {
  static uint32_t fiveSecondTimer = 0;
  static uint32_t flashTimer = 0;
  static uint32_t flashWait = 0;  // value for randomized flash wait
  static uint32_t buttonTimeoutTimer = 0;
  static uint32_t waitStatsTimer = 0;

  // state actions
  switch (currentState) {
    case init_st:
      break;
    case show_info_st:
      break;
    case wait_info_st:
      fiveSecondTimer = 0;  // reset 5 second timer
      break;
    case wait_five_seconds_st:
      fiveSecondTimer++;
      break;
    case blank_screen_st:
      flashTimer = 0; // reset flash timer
      break;
    case wait_between_flash_st:
      flashTimer++;
      break;
    case blink_led_st:
      buttonTimeoutTimer = 0; // reset button timeout timer
      break;
    case wait_for_button_st:
      buttonTimeoutTimer++;
      break;
    case button_pressed_st:
      break;
    case show_stats_st:
      waitStatsTimer = 0;
      break;
    case wait_stats_st:
      waitStatsTimer++;
      break;
    case update_scores_st:
      ReflexTestData_updateScores();
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
    case wait_info_st:
      break;
    case wait_five_seconds_st:
      // Wait here until a user pushes a button and holds it for 5 sec.
      if (fiveSecondTimer >= FIVE_SECOND_WAIT && ReflexTestData_isButtonPressed()) {
        currentState = blank_screen_st;
      }
      // If they let go of the button before 5 sec, go back to waiting.
      else if (!ReflexTestData_isButtonPressed()) {
        currentState = wait_info_st;
      }
      else {
        currentState = wait_five_seconds_st;
      }
      break;
    case blank_screen_st:
      currentState = wait_between_flash_st;
      break;
    case wait_between_flash_st:
      // Seed a random number
      srand((unsigned) ReflexTestData_GetResponseTime());

      // Get a flash wait time between 1 and 3 seconds.
      // e.g. v3 = rand() % 30 + 1985;  <-- v3 in the range 1985-2014
      flashWait = (rand() % TWO_SECOND_WAIT) + ONE_SECOND_WAIT

      // Wait here for flashWait and then blink LED if we're not finished
      if (flashTimer >= flashWait && !ReflexTestData_IsSequenceDone()) {
        currentState = blink_led_st;
      }
      // If we are all done, show stats
      else if (ReflexTestData_IsSequenceDone()) {
        currentState = show_stats_st;
      }
      else {
        currentState = wait_between_flash_st;
      }
      break;
    case blink_led_st:
      currentState = wait_for_button_st;
      break;
    case wait_for_button_st:
      // If the user doesn't push a button within two seconds, start the game over
      if (buttonTimeoutTimer >= TWO_SECOND_WAIT && !ReflexTestData_isCorrectButtonPressed()) {
        currentState = wait_info_st;
      }
      // the moment they do push a button, move states.
      else if (ReflexTestData_isCorrectButtonPressed()) {
        currentState = button_pressed_st;
      }
      else {
        currentState = wait_for_button_st;
      }
      break;
    case button_pressed_st:
      currentState = wait_between_flash_st;
      break;
    case show_stats_st:
      currentState = wait_stats_st;
      break;
    case wait_stats_st:
      if (waitStatsTimer >= FIVE_SECOND_WAIT) {
        currentState = update_scores_st;
      }
      break;
    case update_scores_st:
      break;
   }
  // return the new state.
  return currentState;
}
