#include "Executor.h"
#include "ButtonConductor.h"
#include "Model.h"
#include "Types.h"

void Executor_Init(void) {

  Model_Init();
  ButtonConductor_Init();

}

bool Executor_Run(void) {

  ButtonConductor_Run();

}
