#include "unity.h"
#include "Types.h"

#include "ButtonConductor.h"
#include "mock_ButtonHardware.h"

void setup(void)
{
}

void teardDown(void)
{
}

void testInitShouldCallHardwareInitAndSetButtonGPIOsAsInputs(void)
{
  ButtonHardware_Init_Expect();
  ButtonHardware_SetGPIOsAsInput_Expect();

  ButtonConductor_Init();
}
