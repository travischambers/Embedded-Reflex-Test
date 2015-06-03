#include "ButtonHardware.h"
#include "buttons.h"
#include "intervalTimer.h"

#include <stdio.h>

void ButtonHardware_Init(void) {

  buttons_init(); //sets the buttons as inputs

}

int32_t ButtonHardware_Read() {

  int32_t readButton;
  readButton = buttons_read();

  return readButton;
}

