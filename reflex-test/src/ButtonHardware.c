#include "ButtonHardware.h"
#include "buttons.h"
#include "intervalTimer.h"
#include <stdio.h>

void ButtonHardware_Init(void) {

  buttons_init(); //sets the buttons as inputs

}

int32_t ButtonHardware_Read() {
  return buttons_read();  // Read the value of the buttons and return.
}
