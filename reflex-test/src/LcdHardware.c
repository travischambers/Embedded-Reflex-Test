/*
 * LcdHardware.c
 *
 *  Created on: Jun 3, 2015
 *      Author: travis
 */

#include "LcdHardware.h"
#include "display.h"

void LcdHardware_Init() {
  display_init();
}

void LcdHardware_ShowInfo(double* highScores, int32_t length) {
  display_println("How to play Reflex Test");
  display_println("When the game begins, one of the LEDs will flash on.");
  display_println("You need to press the corresponding button as fast as you can.");
  display_println("Hold any of the buttons to begin the game.");



}

void LcdHardware_BlankScreen(void) {
  display_fillScreen(DISPLAY_BLACK);
}

void LcdHardware_ShowStats(double average, double min, double max) {

//  display_println("Average Time: %lf", average)
//  display_println("Fastest Time: %lf", min)
//  display_println("Slowest Time: %lf", max)

}
