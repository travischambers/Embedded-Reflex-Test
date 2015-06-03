#include "unity.h"
#include "LedConductor.h"
#include "mock_LedModel.h"
#include "mock_LedHardware.h"
#include "mock_intervalTimer.h"
#include <stdbool.h>

void setup() {

}

void tearDown() {

}

void testInitShouldCallModelAndHardwareInit() {
  LedModel_Init_Expect();
  LedHardware_Init_Expect();
  intervalTimer_initAll_ExpectAndReturn(0);
  intervalTimer_start_ExpectAndReturn(INTERVALTIMER_TIMER0, 0);

  LedConductor_Init();
}

void testLedConductor_RunShouldFlashNextLedInSequence() {

  LedModel_IsSequenceDone_ExpectAndReturn(false);
  LedModel_GetNextLed_ExpectAndReturn(1);
  LedHardware_Flash_Expect(1);

  LedConductor_Run();

  LedModel_IsSequenceDone_ExpectAndReturn(true);

  LedConductor_Run();
}
