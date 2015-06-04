#include "unity.h"
#include "LedConductor.h"
#include "mock_LedModel.h"
#include "mock_LedHardware.h"
#include <stdbool.h>

void setup() {

}

void tearDown() {

}

void testInitShouldCallModelAndHardwareInit() {
  LedModel_Init_Expect();
  LedHardware_Init_Expect();

  LedConductor_Init();
}

void testLedConductor_RunShouldDriveStateMachine() {

  LedModel_GetCurrentState_ExpectAndReturn(init_st);

  LedConductor_Run();
}
