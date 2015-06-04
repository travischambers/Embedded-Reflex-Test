#include "unity.h"
#include "ReflexTestData.h"

void setup(void) {
}

void tearDown(void) {
}

void testReflexTestData_InitShouldInitAllStateVariables() {
  // Set the internal state variables to various things
  ReflexTestData_SetResponseTime(1.234);
  ReflexTestData_IncrementIndex();
  ReflexTestData_GenerateSequence(123);
  ReflexTestData_SetPressedButton(0x4);

  // Call Init
  ReflexTestData_Init();

  // Verify that data was re-initialized
  TEST_ASSERT_EQUAL(0, ReflexTestData_GetCurrentIndex());
  TEST_ASSERT_EQUAL(0, ReflexTestData_GetResponseTime());
  TEST_ASSERT_EQUAL(0, ReflexTestData_GetPressedButton());

  // NOTE: Sequence cannot be directly tested, but if the above worked,
  // the sequence will have been cleared as well.
}

void testReflexTestData_CheckIfIsCorrectButtonWorks() {
  // Generate a sequence of:
  // {1, 1, 1, 2, 3, 3, 3, 2, 2, 1};
  ReflexTestData_GenerateSequence(123);

  // Set the button to the correct button
  ReflexTestData_SetPressedButton(0x1);
  TEST_ASSERT_TRUE(ReflexTestData_IsCorrectButtonPressed());

  // Set button to incorrect button
  ReflexTestData_SetPressedButton(0x3);
  TEST_ASSERT_FALSE(ReflexTestData_IsCorrectButtonPressed());
}
