#include "ButtonModel.h"
#include "ReflexTestData.h"

void ButtonModel_Init() {

}

void ButtonModel_SetPressedButton(int32_t value) {
  //defines precedence that users can't press multiple buttons simultaneously
  //button0 has highest precedence, button3 has lowest

  //TODO check value and mask it to only pass the highest precedence button press

    ReflexTestData_SetPressedButton(value);
}


int32_t ButtonModel_GetPressedButton() {
  ReflexTestData_GetPressedButton();
}

