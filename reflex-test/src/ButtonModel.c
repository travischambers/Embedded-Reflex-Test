#include "ButtonModel.h"

void ButtonModel_Init() {

}

void ButtonModel_SetPressedButton(int32_t value) {

  //defines precedence that users can't press multiple buttons simultaneously
  //button0 has highest precedence, button3 has lowest
  value &= ~value + 1; //find the least significant set bit

  // Map button #s to corresponding LED #s
  switch (value) {
    case BUTTONS_BTN0_MASK:
      value = 1;
      break;
    case BUTTONS_BTN1_MASK:
      value = 2;
      break;
    case BUTTONS_BTN2_MASK:
      value = 3;
      break;
    case BUTTONS_BTN3_MASK:
      value = 4;
      break;
  }
  ReflexTestData_SetPressedButton(value);
}

int32_t ButtonModel_GetPressedButton() {
  return ReflexTestData_GetPressedButton();
}

ReflexTest_st ButtonModel_GetCurrentState() {
  return ReflexTestData_GetCurrentState();
}
