/*
 * LcdHardware.c
 *
 *  Created on: Jun 3, 2015
 *      Author: travis
 */

#include "LcdHardware.h"
#include "display.h"

#include <stdio.h>

void LcdHardware_Init() {
  display_init();
  display_fillScreen(DISPLAY_BLACK);
}

void LcdHardware_ShowInfo(double* highScores, int32_t length) {
  display_fillScreen(DISPLAY_BLACK);
  display_setCursor(0,0);

  char str[255];

  display_setTextSize(2);
  display_println("How to play Reflex Test");
  display_setTextSize(1);
  display_println("");
  display_println("When the game begins, one of the LEDs will flash on.");
  display_println("Press the corresponding button as fast as you can.");

  display_println("");

  display_println("Hold any button to begin.");

  display_println("");
  display_println("");
  display_println("");
  display_println("");
  display_println("");
  display_println("");
  display_setTextSize(2);

  display_println("High Scores");

  display_setTextSize(1);

  display_setCursor(0, display_height()/2+10);
  sprintf(str, "1. %lf", highScores[0]);
  display_println(str);

  display_setCursor(0, display_height()/2+20);
  sprintf(str, "2. %lf", highScores[1]);
  display_println("2. ");

  display_setCursor(0, display_height()/2+30);
  sprintf(str, "3. %lf", highScores[2]);
  display_println("3. ");

  display_setCursor(0, display_height()/2+40);
  sprintf(str, "4. %lf", highScores[3]);
  display_println("4. ");

  display_setCursor(0, display_height()/2+50);
  sprintf(str, "5. %lf", highScores[4]);
  display_println("5. ");

  display_setCursor(display_width()/2, display_height()/2+10);
  sprintf(str, "6. %lf", highScores[5]);
  display_println("6. ");

  display_setCursor(display_width()/2, display_height()/2+20);
  sprintf(str, "7. %lf", highScores[6]);
  display_println("7. ");

  display_setCursor(display_width()/2, display_height()/2+30);
  sprintf(str, "8. %lf", highScores[7]);
  display_println("8. ");

  display_setCursor(display_width()/2, display_height()/2+40);
  sprintf(str, "9. %lf", highScores[8]);
  display_println("9. ");

  display_setCursor(display_width()/2, display_height()/2+50);
  sprintf(str, "10. %lf", highScores[9]);
  display_println("10. ");

}

void LcdHardware_BlankScreen(void) {
  display_fillScreen(DISPLAY_BLACK);
}

void LcdHardware_ShowStats(double average, double min, double max) {

  char str[255];
  sprintf(str, "Average Time: %lf", average);
  display_println(str);
  sprintf(str, "Fastest Time: %lf", min);
  display_println(str);
  sprintf(str, "Slowest Time: %lf", max);
  display_println(str);

}
