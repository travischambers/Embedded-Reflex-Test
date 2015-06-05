#include "Executor.h"
#include <stdio.h>
#include <stdbool.h>
#include "../../reflex-test_bsp/ps7_cortexa9_0/include/xil_types.h"
#include "leds.h"
#include "../vendor/supportFiles/utils.h"
#include "../vendor/supportFiles/globalTimer.h"
#include "../vendor/supportFiles/interrupts.h"


#define TOTAL_SECONDS 604800  // 1 week of play time

#define TIMER_PERIOD .001  // 1ms period
#define TIMER_CLOCK_FREQUENCY ((XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ) / 2)
#define TIMER_LOAD_VALUE (((TIMER_PERIOD) * (TIMER_CLOCK_FREQUENCY)) - 1.0)

int runReflexTest() {
  // Initialize the GPIO LED driver and print out an error message if it fails (argument = true).
  leds_init(true);
  // Init all interrupts (but does not enable the interrupts at the devices).
  // Prints an error message if an internal failure occurs because the argument = true.
  interrupts_initAll(true);
  interrupts_setPrivateTimerLoadValue(TIMER_LOAD_VALUE);
  u32 privateTimerTicksPerSecond = interrupts_getPrivateTimerTicksPerSecond();
  printf("private timer ticks per second: %ld\n\r", privateTimerTicksPerSecond);
  // Allow the timer to generate interrupts.
  interrupts_enableTimerGlobalInts();
  Executor_Init();
  // Keep track of your personal interrupt count. Want to make sure that you don't miss any interrupts.
  int32_t personalInterruptCount = 0;
  // Start the private ARM timer running.
  interrupts_startArmPrivateTimer();
  // Enable interrupts at the ARM.
  interrupts_enableArmInts();
  // interrupts_isrInvocationCount() returns the number of times that the timer ISR was invoked.
  // This value is maintained by the timer ISR. Compare this number with your own local
  // interrupt count to determine if you have missed any interrupts.
  while (interrupts_isrInvocationCount() < (TOTAL_SECONDS * privateTimerTicksPerSecond)) {
    if (interrupts_isrFlagGlobal) {  // This is a global flag that is set by the timer interrupt handler.
      // Count ticks.
      personalInterruptCount++;
      Executor_Run();
      interrupts_isrFlagGlobal = 0;
    }
  }
  interrupts_disableArmInts();
  printf("isr invocation count: %ld\n\r", interrupts_isrInvocationCount());
  printf("internal interrupt count: %ld\n\r", personalInterruptCount);
  return 0;
}


int AppMain(void) {
  Executor_Init();

  while(Executor_Run());

  return 0;
}

#ifndef TEST
int main(void) {
  //return AppMain();
  return runReflexTest();
}
#endif // TEST
