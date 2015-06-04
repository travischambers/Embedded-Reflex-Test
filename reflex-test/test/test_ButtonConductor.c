#include "unity.h"
#include "ButtonConductor.h"

#include "mock_ButtonHardware.h"
#include "mock_ButtonModel.h"
#include "mock_buttons.h"

#include <stdint.h>

void setup(void) {
}

void tearDown(void) {
}

void testButtonConductor_InitShouldCallModelAndHardwareInit(void) {
  ButtonModel_Init_Expect();
  ButtonHardware_Init_Expect();

  ButtonConductor_Init();
}

void testButtonConductor_ShouldDoNothingInShowInfoState(void) {
  ButtonModel_GetCurrentState_ExpectAndReturn(show_info_st);
  ButtonConductor_Run();
}

void testButtonConductor_ListenForButtonsInWaitInfoState(void) {

  ButtonModel_GetCurrentState_ExpectAndReturn(wait_info_st);
  ButtonHardware_Read_ExpectAndReturn(BUTTONS_BTN2_MASK);
  ButtonModel_SetPressedButton_Expect(BUTTONS_BTN2_MASK);
  ButtonConductor_Run();

  ButtonModel_GetCurrentState_ExpectAndReturn(wait_info_st);
  ButtonHardware_Read_ExpectAndReturn(BUTTONS_BTN0_MASK);
  ButtonModel_SetPressedButton_Expect(BUTTONS_BTN0_MASK);
  ButtonConductor_Run();

  ButtonModel_GetCurrentState_ExpectAndReturn(wait_info_st);
  ButtonHardware_Read_ExpectAndReturn(BUTTONS_BTN1_MASK);
  ButtonModel_SetPressedButton_Expect(BUTTONS_BTN1_MASK);
  ButtonConductor_Run();
}

void testButtonConductor_ListenForButtonsInWaitFiveSecState(void) {

  ButtonModel_GetCurrentState_ExpectAndReturn(wait_five_seconds_st);
  ButtonHardware_Read_ExpectAndReturn(BUTTONS_BTN2_MASK);
  ButtonModel_SetPressedButton_Expect(BUTTONS_BTN2_MASK);
  ButtonConductor_Run();

  ButtonModel_GetCurrentState_ExpectAndReturn(wait_five_seconds_st);
  ButtonHardware_Read_ExpectAndReturn(BUTTONS_BTN0_MASK);
  ButtonModel_SetPressedButton_Expect(BUTTONS_BTN0_MASK);
  ButtonConductor_Run();

  ButtonModel_GetCurrentState_ExpectAndReturn(wait_five_seconds_st);
  ButtonHardware_Read_ExpectAndReturn(BUTTONS_BTN1_MASK);
  ButtonModel_SetPressedButton_Expect(BUTTONS_BTN1_MASK);
  ButtonConductor_Run();
}

void testButtonConductor_ShouldDoNothingInBlankScreenState(void) {
  ButtonModel_GetCurrentState_ExpectAndReturn(blank_screen_st);
  ButtonConductor_Run();
}

void testButtonConductor_ShouldDoNothingInWaitBetweenFlashState(void) {
  ButtonModel_GetCurrentState_ExpectAndReturn(wait_between_flash_st);
  ButtonConductor_Run();
}

void testButtonConductor_ShouldDoNothingInBlinkLEDState(void) {
  ButtonModel_GetCurrentState_ExpectAndReturn(blink_led_st);
  ButtonConductor_Run();
}

void testButtonConductor_ListenForButtonsInWaitForButtonState(void) {

  ButtonModel_GetCurrentState_ExpectAndReturn(wait_for_button_st);
  ButtonHardware_Read_ExpectAndReturn(BUTTONS_BTN2_MASK);
  ButtonModel_SetPressedButton_Expect(BUTTONS_BTN2_MASK);
  ButtonConductor_Run();

  ButtonModel_GetCurrentState_ExpectAndReturn(wait_for_button_st);
  ButtonHardware_Read_ExpectAndReturn(BUTTONS_BTN0_MASK);
  ButtonModel_SetPressedButton_Expect(BUTTONS_BTN0_MASK);
  ButtonConductor_Run();

  ButtonModel_GetCurrentState_ExpectAndReturn(wait_for_button_st);
  ButtonHardware_Read_ExpectAndReturn(BUTTONS_BTN1_MASK);
  ButtonModel_SetPressedButton_Expect(BUTTONS_BTN1_MASK);
  ButtonConductor_Run();
}

void testButtonConductor_ShouldDoNothingInButtonPressedState(void) {
  ButtonModel_GetCurrentState_ExpectAndReturn(button_pressed_st);
  ButtonConductor_Run();
}

void testButtonConductor_ShouldDoNothingInShowStatsState(void) {
  ButtonModel_GetCurrentState_ExpectAndReturn(show_stats_st);
  ButtonConductor_Run();
}

void testButtonConductor_ShouldDoNothingInWaitStatsState(void) {
  ButtonModel_GetCurrentState_ExpectAndReturn(wait_stats_st);
  ButtonConductor_Run();
}

void testButtonConductor_ShouldDoNothingInUpdateScoresState(void) {
  ButtonModel_GetCurrentState_ExpectAndReturn(update_scores_st);
  ButtonConductor_Run();
}
