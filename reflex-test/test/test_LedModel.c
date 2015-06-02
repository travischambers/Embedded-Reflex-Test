#include "unity.h"
#include "LedModel.h"
#include "mock_LedHardware.h"
#include "mock_LedConductor.h"
#include "mock_leds.h"
#include "mock_intervalTimer.h"

void setup() {

}

void tearDown() {

}

void testInitShouldCallintervalTimer_initAll() {

  intervalTimer_initAll_ExpectAndReturn(0); //0 is success

  LedModel_Init();
}
