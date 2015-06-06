#include "unity.h"
#include "ButtonHardware.h"
#include "mock_ButtonModel.h"
#include "mock_ButtonConductor.h"
#include "mock_buttons.h"
#include "mock_intervalTimer.h"

void setup() {

}

void tearDown() {

}

void testButtonHardware_Init(void) {

 buttons_init_ExpectAndReturn(1);

 ButtonHardware_Init();
}

void testButtonHardware_ReadShouldReturnRawValueFromHardware() {
  int32_t buttonValue = 0;

  buttons_read_ExpectAndReturn(0x1);
  buttonValue = ButtonHardware_Read();
  TEST_ASSERT_EQUAL(0x1, buttonValue);

  buttons_read_ExpectAndReturn(0x2);
  buttonValue = ButtonHardware_Read();
  TEST_ASSERT_EQUAL(0x2, buttonValue);

  buttons_read_ExpectAndReturn(0x3);
  buttonValue = ButtonHardware_Read();
  TEST_ASSERT_EQUAL(0x3, buttonValue);

  buttons_read_ExpectAndReturn(0x4);
  buttonValue = ButtonHardware_Read();
  TEST_ASSERT_EQUAL(0x4, buttonValue);

  buttons_read_ExpectAndReturn(0x4);
  buttonValue = ButtonHardware_Read();
  TEST_ASSERT_EQUAL(0x4, buttonValue);

  buttons_read_ExpectAndReturn(0xF);
  buttonValue = ButtonHardware_Read();
  TEST_ASSERT_EQUAL(0xF, buttonValue);
}
