#include "unity.h"
#include "LedConductor.h"
#include "mock_LedModel.h"
#include "mock_LedHardware.h"
#include <stdbool.h>

void setup() {

}

void tearDown() {

}

void testInitShouldCallModelAndHardwareInit() {
  LedModel_Init_Expect();
  LedHardware_Init_Expect();

  LedConductor_Init();
}

void testLedConductor_RunShouldDriveStateMachine() {

  LedModel_GetCurrentState_ExpectAndReturn(init_st);

  LedConductor_Run();
}

void testLedConductor_InitShouldCallModelAndHardwareInit(void) {
  LedModel_Init_Expect();
  LedHardware_Init_Expect();

  LedConductor_Init();
}

void testLedConductor_ShouldDoNothingInShowInfoState(void) {
  LedModel_GetCurrentState_ExpectAndReturn(show_info_st);
  LedConductor_Run();
}

void testLedConductor_ShouldDoNothingInWaitInfoState(void) {
  LedModel_GetCurrentState_ExpectAndReturn(wait_info_st);
  LedConductor_Run();
}

void testLedConductor_ShouldDoNothingInWaitFiveSecState(void) {
  LedModel_GetCurrentState_ExpectAndReturn(wait_five_seconds_st);
  LedConductor_Run();
}

void testLedConductor_ShouldDoNothingInBlankScreenState(void) {
  LedModel_GetCurrentState_ExpectAndReturn(blank_screen_st);
  LedConductor_Run();
}

void testLedConductor_ShouldDoNothingInWaitBetweenFlashState(void) {
  LedModel_GetCurrentState_ExpectAndReturn(wait_between_flash_st);
  LedConductor_Run();
}

void testLedConductor_TurnOnTheNextLEDInLEDState(void) {
  // NOTE: The interval timer is started by the Timer Conductor
  LedModel_GetCurrentState_ExpectAndReturn(blink_led_st);
  LedModel_GetNextLedAndIncrement_ExpectAndReturn(0x1);
  LedHardware_Enable_Expect(0x1);
  LedConductor_Run();
}

void testLedConductor_ShouldDoNothingInWaitForButtonState(void) {
  LedModel_GetCurrentState_ExpectAndReturn(wait_for_button_st);
  LedConductor_Run();
}

void testLedConductor_TurnOffTheLEDInButtonPressedState(void) {
  LedModel_GetCurrentState_ExpectAndReturn(button_pressed_st);
  LedHardware_BlankAllLeds_Expect();
  LedConductor_Run();
}

void testLedConductor_ShouldDoNothingInShowStatsState(void) {
  LedModel_GetCurrentState_ExpectAndReturn(show_stats_st);
  LedConductor_Run();
}

void testLedConductor_ShouldDoNothingInWaitStatsState(void) {
  LedModel_GetCurrentState_ExpectAndReturn(wait_stats_st);
  LedConductor_Run();
}

void testLedConductor_ShouldDoNothingInUpdateScoresState(void) {
  LedModel_GetCurrentState_ExpectAndReturn(update_scores_st);
  LedConductor_Run();
}
