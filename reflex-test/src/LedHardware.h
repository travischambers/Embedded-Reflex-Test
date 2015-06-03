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

void LedHardware_Flash(int32_t ledNumber);

#endif /* LEDHARDWARE_H */
