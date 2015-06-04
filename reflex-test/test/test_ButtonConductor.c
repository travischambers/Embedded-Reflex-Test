#include "unity.h"
#include "ButtonConductor.h"

#include "mock_ButtonHardware.h"
#include "mock_ButtonModel.h"
#include "mock_buttons.h"

#include <stdint.h>

void setup(void) {
}

void tearDown(void) {
}

void testButtonConductor_InitShouldCallModelAndHardwareInit(void) {
  ButtonModel_Init_Expect();
  ButtonHardware_Init_Expect();

  ButtonConductor_Init();
}

void testButtonConductor_RunShouldMakeButtonsListenForPresses(void) {

  ButtonModel_GetCurrentState_ExpectAndReturn(init_st);

  ButtonConductor_Run();
}
