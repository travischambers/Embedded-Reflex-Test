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

void testInitShouldCallHardwareInitAndSetButtonGPIOsAsInputs(void) {
  ButtonModel_Init_Expect();
  ButtonHardware_Init_Expect();

  ButtonConductor_Init();
}

void testButtonConductor_RunShouldMakeButtonsListenForPresses(void) {

  ButtonHardware_Read_ExpectAndReturn(0x0);
  ButtonModel_SetPressedButton_Expect(0x0);

  ButtonConductor_Run();
}
