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
 * Displays the MIN, MAX, and AVERAGE reponse times
 * from the last round to the user.
 */
void LcdHardware_ShowStats(void);

#endif /* LCDHARDWARE_H_ */
