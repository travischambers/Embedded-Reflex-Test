#ifndef LCDCONDUCTOR_H_
#define LCDCONDUCTOR_H_

/**
 * Initializes the triad for controlling the LCD.
 */
void LcdConductor_Init(void);

/**
 * Performs LCD actions based on the current state.
 */
void LcdConductor_Run(void);

#endif /* LCDCONDUCTOR_H_ */
