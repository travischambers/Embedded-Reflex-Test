/*
 * LcdHardware.h
 *
 *  Created on: Jun 3, 2015
 *      Author: travis
 */

#ifndef LCDHARDWARE_H_
#define LCDHARDWARE_H_

/**
 * Initializes the LCD display.
 */
void LcdHardware_Init(void);

/**
 * Prints out instructions, as well as the top 10 high scores
 * to the screen.
 */
void LcdHardware_ShowInfo(void);

/**
 * Blanks the screen entirely.
 */
void LcdHardware_BlankScreen(void);

/**
 * Displays the MIN, MAX, and AVERAGE response times
 * from the last round to the user.
 * @param average the average time the user took to respond that round
 * @param min     the fastest time the player recorded that round
 * @param max     the slowest time the player recorded that round
 */
void LcdHardware_ShowStats(double average, double min, double max);

#endif /* LCDHARDWARE_H_ */
