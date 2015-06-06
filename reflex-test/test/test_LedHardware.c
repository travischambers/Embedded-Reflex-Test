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

void testLedHardware_InitShouldCallLeds_Init() {
  leds_init_ExpectAndReturn(false, 88);
  LedHardware_Init();
}

void testLedHardware_LEDNumbersMustBeConvertedCorrectly() {
  // Tests that the LED Hardware properly converts from a raw
  // LED number {0, 1, 2, 3, 4} into the bit mask needed by the hardware.

  leds_write_ExpectAndReturn(0x8, 0);
  LedHardware_Enable(4);

  leds_write_ExpectAndReturn(0x4, 0);
  LedHardware_Enable(3);

  leds_write_ExpectAndReturn(0x2, 0);
  LedHardware_Enable(2);

  leds_write_ExpectAndReturn(0x1, 0);
  LedHardware_Enable(1);
}

void testLedHardware_BlankLEDsShouldWriteZeroToHardware() {
  leds_write_ExpectAndReturn(0x0, 0);
  LedHardware_BlankAllLeds();
}
