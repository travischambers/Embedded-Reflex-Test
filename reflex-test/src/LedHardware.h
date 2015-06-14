#ifndef LEDHARDWARE_H
#define LEDHARDWARE_H

#include <stdint.h>

/**
 * Initialization function for the LED Hardware.
 */
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
