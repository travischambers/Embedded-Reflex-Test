#include "unity.h"
#include "TimerHardware.h"

#include "mock_TimerConductor.h"
#include "mock_TimerModel.h"
#include "mock_intervalTimer.h"

void testTimerHardware_InitShouldInitializeTimersAndStartTimer0() {
  intervalTimer_initAll_ExpectAndReturn(0);
  intervalTimer_start_ExpectAndReturn(INTERVALTIMER_TIMER0, 0);

  TimerHardware_Init();
}

void testTimerHardware_StopTimerShouldStopIntervalTimer0() {
  intervalTimer_stop_ExpectAndReturn(INTERVALTIMER_TIMER0, 0);

  TimerHardware_StopTimer();
}

void testTimerHardware_StartTimerShouldStartIntervalTimer0() {
  intervalTimer_start_ExpectAndReturn(INTERVALTIMER_TIMER0, 0);

  TimerHardware_StartTimer();
}

void testTimerHardware_GetResponseTimeShouldReturnDurationThatTheTimerRan() {
  intervalTimer_getTotalDurationInSeconds_IgnoreAndReturn(0);
  TimerHardware_GetResponseTime();
}
