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

void testExecutor_InitShouldCallInitOfAllConductors(void) {
  ButtonConductor_Init_Expect();
  LedConductor_Init_Expect();
  TimerConductor_Init_Expect();
  LcdConductor_Init_Expect();
  ReflexTestData_Init_Expect();

  Executor_Init();
}

void testExecutor_RunShouldCallRunForEachConductorAndReturnTrueAlways(void) {
  // First, read buttons
  ButtonConductor_Run_Expect();

  // Then, manage the timers
  TimerConductor_Run_Expect();

  // Next, work with the sequences and update the index
  LedConductor_Run_Expect();

  // Finally, show the state information. This must be last to have accurate
  // data.
  LcdConductor_Run_Expect();

  ReflexTestData_GetCurrentState_ExpectAndReturn(init_st);
  ReflexTestData_SetCurrentState_Expect(show_info_st);

  TEST_ASSERT_EQUAL(true, Executor_Run());
}
