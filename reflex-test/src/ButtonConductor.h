#ifndef _ButtonConductor_H
#define _ButtonConductor_H


/**
 * ButtonConductor_Init should call the ButtonModel
 * and ButtonHardware Init functions.
 */
void ButtonConductor_Init(void);

/**
 * Called by ReflexTest_tick_function in the executor
 * Drives all button actions
 */
void ButtonConductor_Run(void);

#endif //_ButtonConductor_H
