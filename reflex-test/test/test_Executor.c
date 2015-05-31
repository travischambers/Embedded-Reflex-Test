#include "unity.h"
#include "Types.h"
#include "Executor.h"
#include "mock_ButtonHardware.h"
#include "mock_ButtonModel.h"
#include "mock_ButtonConductor.h"
#include "mock_Model.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void testInitShouldCallInitOfAllConductorsAndTheModel(void)
{
  Model_Init_Expect();
  ButtonConductor_Init_Expect();

  Executor_Init();
}

void testRunShouldCallRunForEachConductorAndReturnTrueAlways(void)
{
  ButtonConductor_Run_Expect();

  TEST_ASSERT_EQUAL(TRUE, Executor_Run());
}
