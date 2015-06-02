#include "unity.h"
#include "LedHardware.h"
#include "mock_LedModel.h"
#include "mock_LedConductor.h"
#include "mock_leds.h"

#include <stdbool.h>

void setup() {

}

void tearDown() {

}

void testInitShouldCallLeds_Init() {

  leds_init_ExpectAndReturn(false, 88);

  LedHardware_Init();
}
