#include "Executor.h"
#include "ButtonConductor.h"
#include "LedConductor.h"

void Executor_Init(void) {

  //call init on each of the conductors
  ButtonConductor_Init();
  LedConductor_Init();
}

bool Executor_Run(void) {

  ButtonConductor_Run();
  LedConductor_Run();
  return true;
}
