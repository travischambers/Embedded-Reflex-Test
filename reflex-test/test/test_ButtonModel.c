#include "unity.h"
#include "ButtonModel.h"
#include "mock_ButtonHardware.h"
#include "mock_ButtonConductor.h"
#include "mock_ReflexTestData.h"

void setup(void) {
}

void tearDown(void) {
}

/**
 * This test tests the masking logic withing SetPressedButton.
 */
void testButtonModel_SetPressedButtonShouldGivePrecedenceToLowestButton(void) {
  // NOTE: The button model itself translates these bit values instructions
  // {0, 1, 2, 3, 4} so that they match up with the generated sequences.
  uint32_t buttonValue = 0xF;
  ReflexTestData_SetPressedButton_Expect(1);
  ButtonModel_SetPressedButton(buttonValue);

  buttonValue = 0x3;
  ReflexTestData_SetPressedButton_Expect(1);
  ButtonModel_SetPressedButton(buttonValue);

  buttonValue = 0x6;
  ReflexTestData_SetPressedButton_Expect(2);
  ButtonModel_SetPressedButton(buttonValue);

  buttonValue = 0x4;
  ReflexTestData_SetPressedButton_Expect(3);
  ButtonModel_SetPressedButton(buttonValue);

  buttonValue = 0x8;
  ReflexTestData_SetPressedButton_Expect(4);
  ButtonModel_SetPressedButton(buttonValue);

  buttonValue = 0xA;
  ReflexTestData_SetPressedButton_Expect(2);
  ButtonModel_SetPressedButton(buttonValue);

  buttonValue = 0x0;
  ReflexTestData_SetPressedButton_Expect(0);
  ButtonModel_SetPressedButton(buttonValue);

  buttonValue = 0x1;
  ReflexTestData_SetPressedButton_Expect(1);
  ButtonModel_SetPressedButton(buttonValue);
}

/**
 * This test just makes sure that the connection is properly made.
 */
void testButtonModel_GetCurrentStateGetsStateFromReflexTestData(void) {
  ReflexTestData_GetCurrentState_ExpectAndReturn(init_st);
  ButtonModel_GetCurrentState();
}

/**
 * This test just makes sure that the connection is properly made.
 */
void testButtonModel_GetPressedButtonFromReflexTestData(void) {
  ReflexTestData_GetPressedButton_ExpectAndReturn(0x1);
  int32_t buttonValue = ButtonModel_GetPressedButton();
  TEST_ASSERT_EQUAL(0x1, buttonValue);
}
