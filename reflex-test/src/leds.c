// Provides easy access to the LEDs.
#include "leds.h"
#include "mio.h"
#include "xgpio.h"
#include "stdio.h"

static XGpio Gpio_LEDs;  // Instance of the LED GPIO Driver
static int initLedFlag = 0;  // This will be '1' if LEDs have been initialized.

// This will init the GPIO hardware so you can write to the 4 LEDs  (LED3 - LED0) on the ZYBO board.
int leds_init(bool printFailedStatusFlag) {
  int status;
  status = XGpio_Initialize(&Gpio_LEDs, XPAR_GPIO_LEDS_DEVICE_ID);
  if (status != XST_SUCCESS) {
	if (printFailedStatusFlag) {
      printf("XGPIO_Initialize (leds) failed\n\r.");
      return 1;
	}
	return 0;
  }
  // Also init LD4, connected to MIO7. Also inits the entire MIO system.
  mio_init(printFailedStatusFlag);
  // Set the direction for all signals to be outputs (0 = output).
  XGpio_SetDataDirection(&Gpio_LEDs, 1, 0);
  initLedFlag=1;
  return 0;
}

// This write the lower 4 bits of ledValue to the LEDs.
// LED3 gets bit3 and so forth.
// '1' = illuminated.
// '0' = off.
int leds_write(int ledValue) {
  if (initLedFlag) {
    XGpio_DiscreteWrite(&Gpio_LEDs, 1, ledValue);
    return 0;
  } else {
	printf("Error: you must invoke initializeLeds() prior to calling writeLeds()\n\r.");
  }
  return 0;
}

// Access LD4 via MIO.
int leds_writeLd4(int ledValue){
  mio_writePin(MIO_LD4_MIO_PIN, ledValue);
  return 0;
}

// This blinks all of the LEDs for several seconds to provide a visual test of the code.
// This will use a simple for-loop as a delay to keep the code independent of other code.
// Always returns 0 because this is strictly a visual test.
#define LEDS_TEST_LENGTH_IN_SECONDS 5
#define LEDS_FOR_LOOP_COUNT_FOR_ONE_BLINK 1000000
int leds_runTest() {
  leds_init(true);
  int i, j;
  for (i=0; i<LEDS_TEST_LENGTH_IN_SECONDS; i++) {
	for (j=0; j<LEDS_FOR_LOOP_COUNT_FOR_ONE_BLINK; j++) {
	  leds_write(0xF);  // All LEDs are turned on.
	  leds_writeLd4(1);
	}
	for (j=0; j<LEDS_FOR_LOOP_COUNT_FOR_ONE_BLINK; j++) {
	  leds_write(0x0);  // All LEDs are turned on.
	  leds_writeLd4(0);
	}
  }
  return 0;
}








