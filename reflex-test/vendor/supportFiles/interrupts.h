/*
 * interrupts.h
 *
 *  Created on: Mar 24, 2014
 *      Author: hutch
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <stdbool.h>
//#include "queue.h"  // If you include queue.h, you can capture ADC samples to a queue (still need to enable it).
#include "xil_types.h"

// Inits all interrupts, which means:
// 1. Sets up the interrupt routine for ARM (GIC ISR) and does all necessary initialization.
// 2. Initializes all supported interrupts and connects their ISRs to the GIC ISR.
// 3. Enables the interrupts at the GIC, but not at the device itself.
// 4. Pretty much does everything but it does not enable the ARM interrupts or any of the device global interrupts.
// if printFailedStatusFlag is true, it prints out diagnostic messages if something goes awry.
int interrupts_initAll(bool printFailedStatusFlag);

int interrupts_enableArmInts();
int interrupts_disableArmInts();

int interrupts_enableTimerGlobalInts();
int interrupts_disableTimerGlobalInts();
int interrupts_setTimerInterval(int loadValue);
int interrupts_startArmPrivateTimer();
int interrupts_stopArmPrivateTimer();
u32 interrupts_getPrivateTimerCounterValue(void);
void interrupts_setPrivateTimerLoadValue(u32 loadValue);
void interrupts_setPrivateTimerPrescalerValue(u32 prescalerValue);

int interrupts_enableSysMonGlobalInts();
int interrupt_disableSysMonGlobalInts();
int interrupts_enableSysMonEocInts();

#ifdef QUEUE_H_
  queue_t *getAdcDataQueue1();
#endif

u32 interrupts_isrInvocationCount();
u32 interrupts_getPrivateTimerTicksPerSecond();
u32 interrupts_getTotalXadcSampleCount();
u32 interrupts_getTotalEocCount();

extern volatile int interrupts_isrFlagGlobal;

#endif /* INTERRUPTS_H_ */
