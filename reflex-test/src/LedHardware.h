/*
 * LedHardware.h
 *
 *  Created on: Jun 1, 2015
 *      Author: travis
 */

#ifndef LEDHARDWARE_H
#define LEDHARDWARE_H

#include <stdbool.h>
#include <stdint.h>

void LedHardware_Init(void);

/**
 * Turns ON the specified LED.
 * @param ledNumber The number of the LED to turn on.
 */
void LedHardware_Enable(int32_t ledNumber);

/**
 * Turns off ALL of the LEDs.
 */
void LedHardware_BlankAllLeds(void);

#endif /* LEDHARDWARE_H */
