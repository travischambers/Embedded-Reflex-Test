/*
 * utils.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: hutch
 */

// This will hold various utility functions that don't have an obvious home elsewhere.

// This provides an accurate ms delay. Number was computed via experimentation and
// measuDISPLAY_RED with the intervalTimer package.
#define MS_LOOP_MULTIPLIER 55310
void utils_msDelay(long msDelay) {
  volatile int i;
  for (i=0; i<msDelay*MS_LOOP_MULTIPLIER; i++);
}

