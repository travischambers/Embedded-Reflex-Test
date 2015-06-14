#ifndef LCDHARDWARE_H_
#define LCDHARDWARE_H_

#include <stdint.h>

/**
 * Initializes the LCD display.
 */
void LcdHardware_Init(void);

/**
 * Displays instructions and the past high scores to the user.
 * @param highScores A pointer to the array of sorted high scores.
 * @param length     The number of high scores in the array.
 */
void LcdHardware_ShowInfo(double* highScores, int32_t length, double newScore);

/**
 * Blanks the screen entirely.
 */
void LcdHardware_BlankScreen(void);

/**
 * Displays the MIN, MAX, and AVERAGE response times
 * from the last round to the user.
 * @param average The average time the user took to respond that round.
 * @param min     The fastest time the player recorded that round.
 * @param max     The slowest time the player recorded that round.
 */
void LcdHardware_ShowStats(double average, double min, double max);

#endif /* LCDHARDWARE_H_ */
