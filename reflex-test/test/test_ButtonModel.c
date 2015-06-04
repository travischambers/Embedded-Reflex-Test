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
  uint32_t buttonValue = 0xF;
  ReflexTestData_SetPressedButton_Expect(0x1);
  ButtonModel_SetPressedButton(buttonValue);

  buttonValue = 0x3;
  ReflexTestData_SetPressedButton_Expect(0x1);
  ButtonModel_SetPressedButton(buttonValue);

  buttonValue = 0x6;
  ReflexTestData_SetPressedButton_Expect(0x2);
  ButtonModel_SetPressedButton(buttonValue);

  buttonValue = 0x4;
  ReflexTestData_SetPressedButton_Expect(0x4);
  ButtonModel_SetPressedButton(buttonValue);

  buttonValue = 0x8;
  ReflexTestData_SetPressedButton_Expect(0x8);
  ButtonModel_SetPressedButton(buttonValue);

  buttonValue = 0xA;
  ReflexTestData_SetPressedButton_Expect(0x2);
  ButtonModel_SetPressedButton(buttonValue);

  buttonValue = 0x0;
  ReflexTestData_SetPressedButton_Expect(0x0);
  ButtonModel_SetPressedButton(buttonValue);

  buttonValue = 0x1;
  ReflexTestData_SetPressedButton_Expect(0x1);
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
