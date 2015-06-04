#include "unity.h"
#include "Executor.h"
#include "mock_ButtonConductor.h"
#include "mock_LedConductor.h"
#include "mock_LcdConductor.h"
#include "mock_TimerConductor.h"
#include "mock_ReflexTestData.h"

void setUp(void) {
}

void tearDown(void) {
}

void testInitShouldCallInitOfAllConductors(void) {
  ButtonConductor_Init_Expect();
  LedConductor_Init_Expect();
  LcdConductor_Init_Expect();
  TimerConductor_Init_Expect();
  ReflexTestData_Init_Expect();

  Executor_Init();
}

void testRunShouldCallRunForEachConductorAndReturnTrueAlways(void) {

  ButtonConductor_Run_Expect();
  LedConductor_Run_Expect();
  LcdConductor_Run_Expect();
  TimerConductor_Run_Expect();
  ReflexTestData_GetCurrentState_ExpectAndReturn(init_st);
  ReflexTestData_SetCurrentState_Expect(show_info_st);

  TEST_ASSERT_EQUAL(true, Executor_Run());
}
