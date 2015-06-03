#include "unity.h"

#include "LcdConductor.h"
#include "mock_LcdHardware.h"
#include "mock_LcdModel.h"

void testLcdConductor_InitShouldCallModelAndHardwareInit() {
  LcdModel_Init_Expect();
  LcdHardware_Init_Expect();

  LcdConductor_Init();
}
