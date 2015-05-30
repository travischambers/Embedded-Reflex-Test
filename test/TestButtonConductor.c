#include "unity.h"
#include "UnityHelper.h"
#include "Types.h"

#include "ButtonConductor.h"
#include "MockButtonConductor.h"
#include "MockButtonModel.h"

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
