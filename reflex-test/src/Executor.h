#ifndef _EXECUTOR_H
#define _EXECUTOR_H

#include <stdbool.h>

/**
 * Initialization function for the executor that initializes all of the
 * conductors in the program.
 */
void Executor_Init(void);

/**
 * Executor Run should be called in a while(1) loop. This in turn drives
 * the execution of the state machine.
 * @return  Always returns TRUE.
 */
bool Executor_Run(void);

#endif // _EXECUTOR_H
