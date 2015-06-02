#include "ButtonConductor.h"
#include "ButtonHardware.h"
#include "ButtonModel.h"
#include "buttons.h"

void ButtonConductor_Init() {
  ButtonModel_Init();
  ButtonHardware_Init();
}

void ButtonConductor_Run() {

    double responseTime;
    int32_t buttonValue = ButtonHardware_Read();
    ButtonModel_SetButtonValue(buttonValue);
    if (buttonValue != 0x0) {
      ButtonHardware_StopTimer();
      responseTime = ButtonHardware_GetResponseTime();
      ButtonModel_SetResponseTime(responseTime);
    }

}
