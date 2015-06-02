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

void ButtonHardware_StopTimer() {
  intervalTimer_stop(INTERVALTIMER_TIMER0);
}

double ButtonHardware_GetResponseTime() {
  double responseTime;
  intervalTimer_getTotalDurationInSeconds(INTERVALTIMER_TIMER0, &responseTime);
  return responseTime;
}
