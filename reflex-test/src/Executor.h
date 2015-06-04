#ifndef _EXECUTOR_H
#define _EXECUTOR_H

#include <stdint.h>
#include <stdbool.h>
#include "ReflexTestData.h"

void Executor_Init(void);
bool Executor_Run(void);

reflexTest_st ReflexTest_tick_Function(reflexTest_st currentState);

#endif // _EXECUTOR_H
