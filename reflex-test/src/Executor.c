#include "Executor.h"
#include "ButtonConductor.h"
#include "LedConductor.h"
#include "TimerConductor.h"
#include "LcdConductor.h"

void Executor_Init(void) {

  //call init on each of the conductors
  ButtonConductor_Init();
  LedConductor_Init();
  LcdConductor_Init();
  TimerConductor_Init();
}

bool Executor_Run(void) {

  ButtonConductor_Run();
  LedConductor_Run();
  LcdConductor_Run();
  TimerConductor_Run();

  return true;
}
