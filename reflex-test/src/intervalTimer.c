//*****************************************************************************
// Luke Hsiao
// 1 May 2015
// Implementation of the AXI Interval Timer Interface
//*****************************************************************************

#include <stdio.h>
#include "../../reflex-test_bsp/ps7_cortexa9_0/include/xil_io.h"
#include "../../reflex-test_bsp/ps7_cortexa9_0/include/xparameters.h"
#include "intervalTimer.h"

/**
 * Helper function for reading timer registers
 * @param  timerNumber ID of the timer (TIMER0, TIMER1 or TIMER2)
 * @param  offset      Register offset from the base address
 * @return             32-bit register value or TIMER_ERROR for invalid numbers
 */
uint32_t intervalTimer_readTimerRegister(uint32_t timerNumber, uint8_t offset) {
  u32 regValue; // Variable to store register value

  // Determine which base address to use based on the timerNumber
  switch (timerNumber) {
    case INTERVALTIMER_TIMER0:  // Read from TIMER0
      regValue = Xil_In32(XPAR_AXI_TIMER_0_BASEADDR + offset);
      break;
    case INTERVALTIMER_TIMER1:  // Read from TIMER1
      regValue = Xil_In32(XPAR_AXI_TIMER_1_BASEADDR + offset);
      break;
    case INTERVALTIMER_TIMER2:  // Read from TIMER2
      regValue = Xil_In32(XPAR_AXI_TIMER_2_BASEADDR + offset);
      break;
    default:  // invalid timer number
      printf("\nERROR: Not a valid timer number.\n\n");
      regValue = INTERVALTIMER_TIMER_ERROR; // Flag the transaction as invalid
      break;
  }
  // cast regValue value to an uint32_t and return value. Return TIMER_ERROR if
  // an error occurred.
  return (uint32_t)regValue;
}

/**
 * Helper function for writing timer registers
 * @param  timerNumber ID of the timer (TIMER0, TIMER1 or TIMER2)
 * @param  offset      Register offset from the base address
 * @param  value       Value to write to the register
 * @return             0 if successful or TIMER_ERROR for invalid numbers
 */
uint32_t intervalTimer_writeTimerRegister(uint32_t timerNumber,
                                          uint8_t offset,
                                          uint32_t value) {

  uint32_t status = 0; // return 0 if successful

  // Determine which baseaddress to use based on timerNumber
  switch (timerNumber) {
    case INTERVALTIMER_TIMER0:  // Write to Timer 0
      Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + offset, value);
      break;
    case INTERVALTIMER_TIMER1:  // Write to Timer 1
      Xil_Out32(XPAR_AXI_TIMER_1_BASEADDR + offset, value);
      break;
    case INTERVALTIMER_TIMER2:  // Write to Timer 2
      Xil_Out32(XPAR_AXI_TIMER_2_BASEADDR + offset, value);
      break;
    default:  // invalid timer number
      printf("\nERROR: Not a valid timer number.\n\n");
      status = INTERVALTIMER_TIMER_ERROR; // Flag the transaction as unsuccessful
      break;
  }
  // return 0 for success, TIMER_ERROR for invalid timer number
  return status;
}

/**
 * Helper function for writing timer registers
 * @param  timerNumber ID of the timer (TIMER0, TIMER1 or TIMER2)
 * @return             Frequency if successful or TIMER_ERROR if invalid number
 */
uint32_t intervalTimer_getTimerFrequency(uint32_t timerNumber) {
  switch (timerNumber) {
    case INTERVALTIMER_TIMER0:  // Get TIMER 0 frequency
      return XPAR_AXI_TIMER_0_CLOCK_FREQ_HZ;
    case INTERVALTIMER_TIMER1:  // Get TIMER 1 frequency
      return XPAR_AXI_TIMER_1_CLOCK_FREQ_HZ;
    case INTERVALTIMER_TIMER2:  // Get TIMER 2 frequency
      return XPAR_AXI_TIMER_2_CLOCK_FREQ_HZ;
    default:  // invalid timer number
      printf("\nERROR: Not a valid timer number.\n\n");
      return INTERVALTIMER_TIMER_ERROR; // Flag the transaction as unsuccessful
  }
}

/**
 * Helper function that sets the ENT0 bit in the passed in value.
 * @param  original The original value
 * @return          The original value with ENT0 bit set
 */
uint32_t intervalTimer_enableENT0(uint32_t original) {
  return (original | INTERVALTIMER_ENABLE_ENT0_MASK); // Set the ENT0 bit to 1
}

/**
 * Helper function that clears the ENT0 bit in the passed in value.
 * @param  original The original value
 * @return          The original value with ENT0 cleared
 */
uint32_t intervalTimer_clearENT0(uint32_t original) {
  return (original & INTERVALTIMER_CLEAR_ENT0_MASK);  // Set the ENT0 bit to 0
}

/**
 * Helper function that sets the CASC bit in the passed in value
 * @param  original The original value
 * @return          The original value with the CASC bit set
 */
uint32_t intervalTimer_enableCASC(uint32_t original) {
  return (original | INTERVALTIMER_ENABLE_CASC_MASK); // Set the CASC bit to 1
}

/**
 * Helper function that sets the LOAD0 bit in the passed in value
 * @param  original The original value
 * @return          The original value with the LOAD0 bit set
 */
uint32_t intervalTimer_enableLOAD0(uint32_t original) {
  return (original | INTERVALTIMER_ENABLE_LOAD0_MASK);  // Set the LOAD0  to 1
}

/**
 * Helper function for reading the 64-bit counter value
 * @param  timerNumber Number of the timer to read
 * @return             64-bit value in the counter
 */
uint64_t intervalTimer_read64bitCounter(uint32_t timerNumber) {

    // variables for reading the 32-bit upper and lower registers
    uint32_t lower_bits, upper_bits, upper_bits_2;

    // Read upper 32-bits of counter
    upper_bits = intervalTimer_readTimerRegister( timerNumber,
                                                  INTERVALTIMER_TCR1_OFFSET);
    // Read lower 32-bits of counter
    lower_bits = intervalTimer_readTimerRegister( timerNumber,
                                                  INTERVALTIMER_TCR0_OFFSET);

    // Read upper bits again
    upper_bits_2 = intervalTimer_readTimerRegister( timerNumber,
                                                    INTERVALTIMER_TCR1_OFFSET);

    // if they differ, read lower bits again
    if (upper_bits_2 != upper_bits) {
      lower_bits = intervalTimer_readTimerRegister( timerNumber,
                                                    INTERVALTIMER_TCR0_OFFSET);
      upper_bits = upper_bits_2;
    }

    // Form the 64-bit cascaded value
    uint64_t counterValue = upper_bits; // store 32-bits in the upper register
    counterValue <<= INTERVALTIMER_REGISTER_WIDTH;
    counterValue |= lower_bits; // add on the lower 32-bits

    return counterValue;
}

uint32_t intervalTimer_start(uint32_t timerNumber) {
  uint32_t csrValue;  // variable to store the original CSR value

  // Check for invalid timer numbers
  if (timerNumber > INTERVALTIMER_TIMER2) {
    // Invalid timerNumber was passed in!
    printf("\nERROR: Not a valid timer number.\n\n");
    return INTERVALTIMER_TIMER_ERROR;
  }

  // Get the current value of control/status register
  csrValue = intervalTimer_readTimerRegister( timerNumber,
                                              INTERVALTIMER_TCSR0_OFFSET);

  // Write value back w/ ENT0 enabled
  intervalTimer_writeTimerRegister( timerNumber, // timer number
                                    INTERVALTIMER_TCSR0_OFFSET, // reg offset
                                    intervalTimer_enableENT0(csrValue));

  return 0;  // return 0 for success, or TIMER_ERROR
}

uint32_t intervalTimer_stop(uint32_t timerNumber) {
  uint32_t csrValue;  // variable to store the original CSR value

  // Check for invalid timer numbers
  if (timerNumber > INTERVALTIMER_TIMER2) {
    // Invalid timerNumber was passed in!
    printf("\nERROR: Not a valid timer number.\n\n");
    return INTERVALTIMER_TIMER_ERROR;
  }

  // Get the current value of control/status register
  csrValue = intervalTimer_readTimerRegister( timerNumber,
                                              INTERVALTIMER_TCSR0_OFFSET);

  // Write value back w/ ENT0 enabled
  intervalTimer_writeTimerRegister( timerNumber, // timer number
                                    INTERVALTIMER_TCSR0_OFFSET, // reg offset
                                    intervalTimer_clearENT0(csrValue));

  return 0;  // return 0 for success, or TIMER_ERROR
}

uint32_t intervalTimer_reset(uint32_t timerNumber) {
  uint32_t csrValue;  // variable to store the original CSR value

  // Check for invalid timer numbers
  if (timerNumber > INTERVALTIMER_TIMER2) {
    // Invalid timerNumber was passed in!
    printf("\nERROR: Not a valid timer number.\n\n");
    return INTERVALTIMER_TIMER_ERROR;
  }

  // Store 0 in TLR0
  intervalTimer_writeTimerRegister(timerNumber, INTERVALTIMER_TLR0_OFFSET, 0);

  // Get the current value of control/status register
  csrValue = intervalTimer_readTimerRegister( timerNumber,
                                              INTERVALTIMER_TCSR0_OFFSET);

  // Write value back w/ LOAD0 enabled
  intervalTimer_writeTimerRegister( timerNumber, // timer number
                                    INTERVALTIMER_TCSR0_OFFSET, // reg offset
                                    intervalTimer_enableLOAD0(csrValue));

  // Store 0 in TLR1
  intervalTimer_writeTimerRegister(timerNumber, INTERVALTIMER_TLR1_OFFSET, 0);

  // Get the current value of control/status register
  csrValue = intervalTimer_readTimerRegister( timerNumber,
                                              INTERVALTIMER_TCSR1_OFFSET);

  // Write value back w/ LOAD0 enabled
  intervalTimer_writeTimerRegister( timerNumber, // timer number
                                    INTERVALTIMER_TCSR1_OFFSET, // reg offset
                                    intervalTimer_enableLOAD0(csrValue));

  intervalTimer_init(timerNumber);

  return 0;  // return 0 for success, or TIMER_ERROR
}

uint32_t intervalTimer_init(uint32_t timerNumber) {

  // Check for invalid timer numbers
  if (timerNumber > INTERVALTIMER_TIMER2) {
    // Invalid timerNumber was passed in!
    printf("\nERROR: Not a valid timer number.\n\n");
    return INTERVALTIMER_TIMER_ERROR;
  }

  // Write 0 to TCSR0
  intervalTimer_writeTimerRegister( timerNumber, // timer number
                                    INTERVALTIMER_TCSR0_OFFSET, // reg offset
                                    0x0000);

  // Write 0 to TCSR1
  intervalTimer_writeTimerRegister( timerNumber, // timer number
                                    INTERVALTIMER_TCSR1_OFFSET, // reg offset
                                    0x0000);

  // Set cascade bit. Note that since TCSR was set to zero, timer counts up
  intervalTimer_writeTimerRegister( timerNumber, // timer number
                                    INTERVALTIMER_TCSR0_OFFSET, // reg offset
                                    intervalTimer_enableCASC(0));


  return 0;  // return 0 for success, or TIMER_ERROR
}

uint32_t intervalTimer_initAll() {
  uint32_t status;  // variable to check all inits for errors

  // Iterate over all of the timers and initialize them
  int i;
  for (i = 0; i <= INTERVALTIMER_TIMER2; i++) {
    status = intervalTimer_init(i);

    // If an error occurred, break and return TIMER_ERROR
    if (status != 0) {
      return status;
    }
  }

  return 0; // return 0 on success, TIMER_ERROR on failure
}

uint32_t intervalTimer_resetAll() {
  uint32_t status;  // variable to check all resets for errors

  // Iterate over all of the timers and reset them
  int i;
  for (i = 0; i <= INTERVALTIMER_TIMER2; i++) {
    status = intervalTimer_reset(i);

    // If an error occurred, break and return TIMER_ERROR
    if (status != 0) {
      return status;
    }
  }

  return 0; // return 0 on success, TIMER_ERROR on failure
}

uint32_t intervalTimer_testAll() {
  uint32_t status;  // variable to check all tests for errors

  // Iterate over all of the timers and test them
  int i;
  for (i = 0; i <= INTERVALTIMER_TIMER2; i++) {
    status = intervalTimer_runTest(i);

    // If an error occurred, break and return TIMER_ERROR
    if (status != 0) {
      return status;
    }
  }

  return 0; // return 0 on success, TIMER_ERROR on failure
}

uint32_t intervalTimer_runTest(uint32_t timerNumber) {

  uint32_t status = 0;
  double seconds = 0;

  // Check for invalid timer numbers
  if (timerNumber > INTERVALTIMER_TIMER2) {
    // Invalid timerNumber was passed in!
    printf("\nERROR: Not a valid timer number.\n\n");
    return INTERVALTIMER_TIMER_ERROR;
  }

  intervalTimer_init(timerNumber);  // Initialize the timer

  // reset the timer
  printf("Resetting timer %d\n", (int) timerNumber);
  status = intervalTimer_reset(timerNumber);  // keep track of status

  // Check that timer is reset
  printf("Counter value should be ZERO:\n\t");

  // keep track of status
  status = intervalTimer_getTotalDurationInSeconds(timerNumber, &seconds);
  printf("Timer %d: Counter Value = %f\n", (int) timerNumber, seconds);

  // Start the Timer and show that it is running
  printf("Starting the timer...\n");
  status = intervalTimer_start(timerNumber);  // keep track of status

  printf("Timer value should be changing:\n\t");
  // Read the timer register several times to verify different values are seen
  printf("TCR0:%ld\n\t", intervalTimer_readTimerRegister(timerNumber, INTERVALTIMER_TCR0_OFFSET));
  printf("TCR0:%ld\n\t", intervalTimer_readTimerRegister(timerNumber, INTERVALTIMER_TCR0_OFFSET));
  printf("TCR0:%ld\n\t", intervalTimer_readTimerRegister(timerNumber, INTERVALTIMER_TCR0_OFFSET));
  printf("TCR0:%ld\n", intervalTimer_readTimerRegister(timerNumber, INTERVALTIMER_TCR0_OFFSET));

  // Stop the timer
  printf("Stopping the timer...\n");
  status = intervalTimer_stop(timerNumber); // keep track of status

  printf("Timer value should NOT be changing:\n\t");
  // Read the timer register several times to verify that values don't change
  printf("TCR0:%ld\n\t", intervalTimer_readTimerRegister(timerNumber, INTERVALTIMER_TCR0_OFFSET));
  printf("TCR0:%ld\n\t", intervalTimer_readTimerRegister(timerNumber, INTERVALTIMER_TCR0_OFFSET));
  printf("TCR0:%ld\n\t", intervalTimer_readTimerRegister(timerNumber, INTERVALTIMER_TCR0_OFFSET));
  printf("TCR0:%ld\n", intervalTimer_readTimerRegister(timerNumber, INTERVALTIMER_TCR0_OFFSET));

  // If an error occured in any of the steps in the test, print an ERROR msg
  if (status != 0) {
    printf("\n>>>> AN ERROR OCCURED <<<<\n\n");
  }
  return status;  // return 0 for success, or TIMER_ERROR
}

uint32_t intervalTimer_getTotalDurationInSeconds( uint32_t timerNumber,
                                                  double *seconds) {
  double clockCycles = intervalTimer_read64bitCounter(timerNumber);
  double frequency = intervalTimer_getTimerFrequency(timerNumber);

  // Convert from clock cycles to seconds and store value
  *seconds = clockCycles / frequency;

  return 0;
}
