#include "unity.h"
#include "Types.h"
#include "Executor.h"

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
