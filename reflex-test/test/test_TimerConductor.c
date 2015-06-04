#include "unity.h"
#include "TimerConductor.h"

#include "mock_TimerHardware.h"
#include "mock_TimerModel.h"
#include "mock_intervalTimer.h"

void setup(void) {
}

void tearDown(void) {
}

void testTimerConductorInitShouldCallHardwareInitAndModelInit() {
  TimerHardware_Init_Expect();
  TimerModel_Init_Expect();

  TimerConductor_Init();
}

void testTimerConductor_InitShouldCallModelAndHardwareInit(void) {
  TimerModel_Init_Expect();
  TimerHardware_Init_Expect();

  TimerConductor_Init();
}

void testTimerConductor_ResetAndStartTimerInShowInfoState(void) {
  TimerModel_GetCurrentState_ExpectAndReturn(show_info_st);
  TimerHardware_ResetTimer_Expect();
  TimerHardware_StartTimer_Expect();
  TimerConductor_Run();
}

void testTimerConductor_ShouldDoNothingInWaitInfoState(void) {
  TimerModel_GetCurrentState_ExpectAndReturn(wait_info_st);
  TimerConductor_Run();
}

void testTimerConductor_ShouldDoNothingInWaitFiveSecState(void) {
  TimerModel_GetCurrentState_ExpectAndReturn(wait_five_seconds_st);
  TimerConductor_Run();
}

void testTimerConductor_StopTimerInBlankScreenAndClearStatsState(void) {
  TimerModel_GetCurrentState_ExpectAndReturn(blank_screen_st);
  TimerHardware_StopTimer_Expect();
  TimerHardware_GetResponseTime_ExpectAndReturn(8.88);
  TimerModel_SetResponseTime_Expect(8.88);
  TimerModel_ClearOldStats_Expect();
  TimerConductor_Run();
}

void testTimerConductor_ShouldDoNothingInWaitBetweenFlashState(void) {
  TimerModel_GetCurrentState_ExpectAndReturn(wait_between_flash_st);
  TimerConductor_Run();
}

void testTimerConductor_TurnOnTheTimerInBlinkLEDState(void) {
  TimerModel_GetCurrentState_ExpectAndReturn(blink_ledr_st);
  TimerHardware_ResetTimer_Expect();
  TimerHardware_StartTimer_Expect();
  TimerConductor_Run();
}

void testTimerConductor_ShouldDoNothingInWaitForButtonState(void) {
  TimerModel_GetCurrentState_ExpectAndReturn(wait_for_button_st);
  TimerConductor_Run();
}

void testTimerConductor_TurnOffTheTimerInButtonPressedState(void) {
  TimerModel_GetCurrentState_ExpectAndReturn(button_pressed_st);
  TimerHardware_StopTimer_Expect();
  TimerHardware_GetResponseTime_ExpectAndReturn(8.88);
  TimerModel_SetResponseTime_Expect(8.88);
  TimerConductor_Run();
}

void testTimerConductor_CalculateStatesAndProvideInfoInShowStatsState(void) {
  TimerModel_GetCurrentState_ExpectAndReturn(show_stats_st);
  TimerModel_CalculateStats_Expect();
  TimerModel_GetMin_ExpectAndReturn(0.098);
  TimerModel_GetMax_ExpectAndReturn(0.612);
  TimerModel_GetAverage_ExpectAndReturn(0.123);
  TimerConductor_Run();
}

void testTimerConductor_ShouldDoNothingInWaitStatsState(void) {
  TimerModel_GetCurrentState_ExpectAndReturn(wait_stats_st);
  TimerConductor_Run();
}

void testTimerConductor_ShouldDoNothingInUpdateScoresState(void) {
  TimerModel_GetCurrentState_ExpectAndReturn(update_scores_st);
  TimerConductor_Run();
}
