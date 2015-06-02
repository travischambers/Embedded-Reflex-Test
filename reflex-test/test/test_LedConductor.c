#include "unity.h"
#include "LedConductor.h"
#include "mock_LedModel.h"
#include "mock_LedHardware.h"

void setup() {

}

void tearDown() {

}

void testInitShouldCallModelAndHardwareInit() {
  LedModel_Init_Expect();
  LedHardware_Init_Expect();

  LedConductor_Init();
}
