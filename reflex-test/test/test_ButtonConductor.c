#include "unity.h"

#include "ButtonConductor.h"
#include "mock_ButtonHardware.h"

#include <stdint.h>

void setup(void)
{
}

void teardDown(void)
{
}

void testInitShouldCallHardwareInitAndSetButtonGPIOsAsInputs(void)
{
  ButtonHardware_Init_Expect();

  ButtonConductor_Init();
}
