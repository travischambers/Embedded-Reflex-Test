#include "ButtonModel.h"

void ButtonModel_Init() {

}

void ButtonModel_SetPressedButton(int32_t value) {

  //defines precedence that users can't press multiple buttons simultaneously
  //button0 has highest precedence, button3 has lowest
  uint32_t unsignedValue = value;
  unsignedValue &= ~unsignedValue + 1; //find the least significant set bit

  ReflexTestData_SetPressedButton((int32_t) unsignedValue);
}

int32_t ButtonModel_GetPressedButton() {
  ReflexTestData_GetPressedButton();
}

ReflexTest_st ButtonModel_GetCurrentState() {
  return ReflexTestData_GetCurrentState();
}
