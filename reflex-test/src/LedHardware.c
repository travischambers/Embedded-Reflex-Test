/*
 * LedHardware.c
 *
 *  Created on: Jun 1, 2015
 *      Author: travis
 */

#include "LedHardware.h"
#include "leds.h"
#include <stdbool.h>

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void LedHardware_Init() {

  int32_t ledValue;
  ledValue = leds_init(false);
  printf("%ld\n", ledValue);

}

void LedHardware_Enable(int32_t ledNumber) {
  leds_write((int)ledNumber);
}

void LedHardware_BlankAllLeds() {
  // Turn off all of the LEDs
  leds_write(0x0);
}
