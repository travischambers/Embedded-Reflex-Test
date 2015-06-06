#include "unity.h"
#include "LcdConductor.h"

#include "mock_LcdHardware.h"
#include "mock_LcdModel.h"
#include "mock_ReflexTestData.h"

void testLcdConductor_InitShouldCallModelAndHardwareInit() {
  LcdModel_Init_Expect();
  LcdHardware_Init_Expect();

  LcdConductor_Init();
}

void testLcdConductor_DisplayInfoInShowInfoState(void) {
  LcdModel_GetCurrentState_ExpectAndReturn(show_info_st);
  LcdModel_GetHighScores_ExpectAndReturn(NULL);
  LcdModel_GetAverageResponseTime_ExpectAndReturn(1.23);
  LcdHardware_ShowInfo_Expect(NULL, REFLEXTESTDATA_NUMBER_OF_HIGH_SCORES, 1.23);
  LcdConductor_Run();
}

void testLcdConductor_ShouldDoNothingInWaitInfoState(void) {
  LcdModel_GetCurrentState_ExpectAndReturn(wait_info_st);
  LcdConductor_Run();
}

void testLcdConductor_ShouldDoNothingInWaitFiveSecState(void) {
  LcdModel_GetCurrentState_ExpectAndReturn(wait_five_seconds_st);
  LcdConductor_Run();
}

void testLcdConductor_BlankScreeninBlankScreenState(void) {
  LcdModel_GetCurrentState_ExpectAndReturn(blank_screen_st);
  LcdHardware_BlankScreen_Expect();
  LcdConductor_Run();
}

void testLcdConductor_ShouldDoNothingInWaitBetweenFlashState(void) {
  LcdModel_GetCurrentState_ExpectAndReturn(wait_between_flash_st);
  LcdConductor_Run();
}

void testLcdConductor_DoNothingInBlinkLEDState(void) {
  LcdModel_GetCurrentState_ExpectAndReturn(blink_led_st);
  LcdConductor_Run();
}

void testLcdConductor_ShouldDoNothingInWaitForButtonState(void) {
  LcdModel_GetCurrentState_ExpectAndReturn(wait_for_button_st);
  LcdConductor_Run();
}

void testLcdConductor_DoNothingInButtonPressedState(void) {
  LcdModel_GetCurrentState_ExpectAndReturn(button_pressed_st);
  LcdConductor_Run();
}

void testLcdConductor_DisplayStatsInShowStatsState(void) {
  LcdModel_GetCurrentState_ExpectAndReturn(show_stats_st);
  LcdModel_GetAverageResponseTime_ExpectAndReturn(1.2345);
  LcdModel_GetMinResponseTime_ExpectAndReturn(2.3456);
  LcdModel_GetMaxResponseTime_ExpectAndReturn(3.4567);
  LcdHardware_ShowStats_Expect(1.2345, 2.3456, 3.4567);
  LcdConductor_Run();
}

void testLcdConductor_ShouldDoNothingInWaitStatsState(void) {
  LcdModel_GetCurrentState_ExpectAndReturn(wait_stats_st);
  LcdConductor_Run();
}

void testLcdConductor_BlankScreenInUpdateScoresState(void) {
  LcdModel_GetCurrentState_ExpectAndReturn(update_scores_st);
  LcdHardware_BlankScreen_Expect();
  LcdConductor_Run();
}
