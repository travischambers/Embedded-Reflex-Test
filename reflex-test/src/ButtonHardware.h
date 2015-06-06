#ifndef _ButtonHardware_H
#define _ButtonHardware_H

#include <stdint.h>

/**
 * Calls buttons_init to set the button GPIOs as inputs
 */
void ButtonHardware_Init(void);

/**
 * This reads the value of the GPIORegister
 * @return  The value of the buttons being read
 * BUTTONS_BTN0_MASK       0x1
 * BUTTONS_BTN1_MASK       0x2
 * BUTTONS_BTN2_MASK       0x4
 * BUTTONS_BTN3_MASK       0x8
 * If multiple buttons are pressed the total value is returned.
 */
int32_t ButtonHardware_Read(void);


#endif //_ButtonHardware_H
