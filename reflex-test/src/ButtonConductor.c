#include "ButtonConductor.h"
#include "ButtonHardware.h"
#include "ButtonModel.h"
#include "buttons.h"

void ButtonConductor_Init() {
  ButtonModel_Init();
  ButtonHardware_Init();
}

void ButtonConductor_Run() {

  // if (in waiting_for_response state)
    int32_t buttonValue = ButtonHardware_Read();
    ButtonModel_SetPressedButton(buttonValue);
    if (buttonValue != 0x0) {
//TODO move to TimerConductor      ButtonHardware_StopTimer();
//TODO move.... somewhere      responseTime = ButtonHardware_GetResponseTime();
//TODO move to TimerConductor      ButtonModel_SetResponseTime(responseTime);
    }
}
