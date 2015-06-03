#include "unity.h"
#include "TimerConductor.h"

#include "mock_TimerHardware.h"
#include "mock_TimerModel.h"
#include "mock_intervalTimer.h"

void setup(void) {
}

void tearDown(void) {
}

void testTimerConductorInitShouldCallHardwareInitAndModelInit() {
  TimerHardware_Init_Expect();
  TimerModel_Init_Expect();

  TimerConductor_Init();
}
