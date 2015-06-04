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

  //TODO figure out what "seconds" needs to be to have test pass
  // double seconds = 10.85;
  // double secondsToReturn = 10.85;
  //
  // intervalTimer_getTotalDurationInSeconds_IgnoreAndReturn(1);
  // intervalTimer_getTotalDurationInSeconds_ReturnThruPtr_seconds(&secondsToReturn);
  //
  // TimerHardware_GetResponseTime();
  //
  // TEST_ASSERT_EQUAL(secondsToReturn, seconds);
}
