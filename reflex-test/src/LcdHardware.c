#include "LcdHardware.h"
#include "display.h"
#include "math.h"

#include <stdio.h>

#define LINE_HEIGHT   10
#define CENTERED_Y    (display_height()/2)
#define CENTERED_X    (display_width()/2)
#define TEXTSIZE_H1   4
#define TEXTSIZE_H2   2
#define TEXTSIZE_H3   1
#define MAX_STR_LEN   255

void LcdHardware_Init() {
  display_init();
  display_fillScreen(DISPLAY_BLACK);
}

void LcdHardware_ShowInfo(double* highScores, int32_t length, double newScore) {
  double epsilon = 0.0000001; // used for checking float equality

  // Blank the screen and set the cursor to the top left corner.
  display_fillScreen(DISPLAY_BLACK);
  display_setCursor(0,0);

  char str[MAX_STR_LEN];  // Create a buffer for printing.

  display_setTextSize(TEXTSIZE_H2);
  display_println("How to play Reflex Test");
  display_setTextSize(TEXTSIZE_H3);
  display_println("");
  display_println("When the game begins, one of the LEDs will flash on.");
  display_println("Press the corresponding button as fast as you can.");

  display_println("");

  display_println("Hold any button for 5 seconds to begin.");

  display_println("");
  display_println("");
  display_println("");
  display_println("");
  display_println("");
  display_println("");
  display_setTextSize(TEXTSIZE_H2);

  display_println("High Scores");

  display_setTextSize(TEXTSIZE_H3);

  // Begin printing out the 10 high scores.
  int i;
  for (i = 0; i < 5; i++) {
    display_setCursor(0, CENTERED_Y + (LINE_HEIGHT*(i+1)));
    sprintf(str, "%d. %lf sec", (i+1), highScores[i]);
    // highlight the newest high score.
    // NOTE: if user plays but doesn't make high scores, no score is highlighted
    if(fabs(highScores[i] - newScore) < epsilon) {
      display_setTextColor(DISPLAY_GREEN);
    }
    else {
      display_setTextColor(DISPLAY_WHITE);
    }
    display_println(str);
  }

  for (i = 5; i < 10; i++) {
    display_setCursor(CENTERED_X, CENTERED_Y + (LINE_HEIGHT*(i-4)));
    sprintf(str, "%d. %lf sec", (i+1), highScores[i]);
    // highlight the newest high score.
    if(fabs(highScores[i] - newScore) < epsilon) {
      display_setTextColor(DISPLAY_GREEN);
    }
    else {
      display_setTextColor(DISPLAY_WHITE);
    }
    display_println(str);
  }
}

void LcdHardware_BlankScreen(void) {
  display_fillScreen(DISPLAY_BLACK);  // blank the screen.
}

void LcdHardware_ShowStats(double average, double min, double max) {
  display_setCursor(0, 0);  // set cursor to origin
  display_setTextSize(TEXTSIZE_H2); // Make Text Larger
  char str[MAX_STR_LEN];  // buffer for characters

  // Print all the stats
  sprintf(str, "Average Time: %lf sec", average);
  display_println(str);
  sprintf(str, "Fastest Time: %lf sec", min);
  display_println(str);
  sprintf(str, "Slowest Time: %lf sec", max);
  display_println(str);

}
