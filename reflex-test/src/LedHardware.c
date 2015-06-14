#include "LedHardware.h"
#include "leds.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void LedHardware_Init() {
  int32_t ledValue;
  ledValue = leds_init(false);  // call init on the hardware
  printf("%ld\n", ledValue);
}

void LedHardware_Enable(int32_t ledNumber) {
  int value = 0;
  // Map kedNumber #s to corresponding LED #s
  switch (ledNumber) {
    case 1:
      value = 0x1;
      break;
    case 2:
      value = 0x2;
      break;
    case 3:
      value = 0x4;
      break;
    case 4:
      value = 0x8;
      break;
  }
  leds_write(value);
}

void LedHardware_BlankAllLeds() {
  // Turn off all of the LEDs
  leds_write(0x0);
}
