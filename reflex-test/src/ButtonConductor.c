#include "ButtonConductor.h"
#include "ButtonHardware.h"

void ButtonConductor_Init() {
  ButtonHardware_Init();
  ButtonHardware_SetGPIOsAsInput();
}

void ButtonConductor_Run() {

}
