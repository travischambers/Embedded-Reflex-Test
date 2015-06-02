#include "ButtonModel.h"

static int32_t buttonValue = 0;
static double responseTime = 0;
void ButtonModel_Init() {

}


void ButtonModel_SetButtonValue(int32_t value) {

    buttonValue = value;
}


int32_t ButtonModel_GetPressedButton() {
  //defines precedence that users can't press multiple buttons simultaneously
  //button0 has highest precedence, button3 has lowest

}

void ButtonModel_SetResponseTime(double time) {
 responseTime = time;
}
