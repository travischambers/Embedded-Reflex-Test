#include "unity.h"
#include "LedModel.h"
#include "mock_LedHardware.h"
#include "mock_LedConductor.h"
#include "mock_ReflexTestData.h"

void setup() {

}

void tearDown() {

}

void testLedModel_ShouldIncrementIndexOfReflexTestData() {
  ReflexTestData_IncrementIndex_Expect();
  LedModel_IncrementIndex();
}

void testLedModel_ShouldGetCurrentStateFromReflexTestData() {
  ReflexTestData_GetCurrentState_ExpectAndReturn(init_st);
  ReflexTest_st test = LedModel_GetCurrentState();
  TEST_ASSERT_EQUAL(init_st, test);
}

void testLedModel_GetNextLedShouldGetLedFromReflexTestData() {
  ReflexTestData_GetNextLed_ExpectAndReturn(0x1);
  int32_t test = LedModel_GetNextLed();
  TEST_ASSERT_EQUAL(0x1, test);
}
