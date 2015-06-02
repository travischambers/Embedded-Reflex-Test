#include "ButtonConductor.h"
#include "ButtonHardware.h"
#include "ButtonModel.h"
#include "buttons.h"

void ButtonConductor_Init() {
  ButtonModel_Init();
  ButtonHardware_Init();
}

void ButtonConductor_Run() {

}
