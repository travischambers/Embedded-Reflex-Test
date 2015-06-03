//*****************************************************************************
// Luke Hsiao
// 29 April 2015
// Driver file for interacting with the buttons
//*****************************************************************************

#include <stdio.h>
#include "buttons.h"
#include "../../reflex-test_bsp/ps7_cortexa9_0/include/xparameters.h"
#include "display.h"

// Screen Position Macros
#define FOURTH(X)         ((X)/4) // Divide the given number by 4
#define HALF(X)           ((X)/2) // Divide the given number by 2
#define THREE_FOURTHS(X)  (((X) * 3)/4) // Multiply by 3, then divide by 4

// Globals to track button statuses
uint8_t btn0_status = BUTTONS_NOT_SET;  // Initialize as NOT_SET
uint8_t btn1_status = BUTTONS_NOT_SET;  // Initialize as NOT_SET
uint8_t btn2_status = BUTTONS_NOT_SET;  // Initialize as NOT_SET
uint8_t btn3_status = BUTTONS_NOT_SET;  // Initialize as NOT_SET

// Global Screen size values
uint16_t x_max;   // Store the maximum x-value of the screen
uint16_t y_max;   // Store the maximum y-value of the screen

// Values of screen positions
uint16_t x_fourth;  // x-value of the left fourth of the screen
uint16_t x_half;    // x-value of the middle of the screen
uint16_t x_three_fourths;   // x-value of right fourth of the screen
uint16_t y_fourth;  // y-value of the top fourth of the screen
uint16_t y_half;    // y-value of the middle of the screen
uint16_t y_three_fourths; // y-value of the bottom fourth of the screen


//************************* Helper Functions **********************************

// Helper function to read GPIO registers.
// @param offset offset from the base address to read from
int32_t buttons_readGpioRegister(int32_t offset) {
  // Casted to (uint32_t *) to match data types
  uint32_t *ptr = (uint32_t *)XPAR_GPIO_PUSH_BUTTONS_BASEADDR + offset;
  return *ptr;
}

// Helper function to write GPIO registers.
// @param offset offset from the base address to write to
// @param value 32-bit value to write to the register
void buttons_writeGpioRegister(int32_t offset, uint32_t value) {
  // Casted to (uint32_t *) to match data types
  uint32_t *ptr = (uint32_t *)XPAR_GPIO_PUSH_BUTTONS_BASEADDR + offset;
  *ptr = value;
}

// Helper function to write data to the LCD based on what button is pressed,
// blanks the screen otherwise.
void buttons_write_LCD(int32_t buttons) {

  // If BTN 0 is pressed
  if (buttons & BUTTONS_BTN0_MASK) {
    // check if btn0 is set so image is only drawn once
    if (btn0_status == BUTTONS_NOT_SET) {
      // Draw the background colored rectangle
      display_fillRect(x_three_fourths, 0, x_fourth, y_max, DISPLAY_CYAN);

      // Print BTN text in the middle of the rectangle
      display_setCursor(x_three_fourths, y_half); // position cursor
      display_println(" BTN 0");

      // Mark the button as SET so that there is no flickering of the image
      btn0_status = BUTTONS_SET;
    }
  }
  else {
    // Blank the used portion of the screen
    display_fillRect(x_three_fourths, 0, x_fourth, y_max, DISPLAY_BLACK);
    btn0_status = BUTTONS_NOT_SET; // mark btn0 as not set
  }

  // If BTN 1 is pressed
  if (buttons & BUTTONS_BTN1_MASK) {
    // Only draw image once
    if (btn1_status == BUTTONS_NOT_SET) {
      // Draw the background colored rectangle
      display_fillRect(x_half, 0, x_fourth, y_max, DISPLAY_YELLOW);

      // Print BTN text in the middle of the rectangle
      display_setCursor(x_half, y_half);  // position the cursor
      display_println(" BTN 1");

      // Mark the button as SET to eliminate flickering
      btn1_status = BUTTONS_SET;
    }
  }
  else {
    // Blank the used portion of the screen
    display_fillRect(x_half, 0, x_fourth, y_max, DISPLAY_BLACK);
    btn1_status = BUTTONS_NOT_SET;
  }

  // If BTN 2 is pressed
  if (buttons & BUTTONS_BTN2_MASK) {
    // Only draw image once
    if (btn2_status == BUTTONS_NOT_SET) {
      // Draw the background colored rectangle
      display_fillRect(x_fourth, 0, x_fourth, y_max, DISPLAY_GREEN);

      // Print BTN text in the middle of the rectangle
      display_setCursor(x_fourth, y_half);  // Position the cursor
      display_println(" BTN 2");

      // Mark the button as SET to eliminate flickering
      btn2_status = BUTTONS_SET;
    }
  }
  else {
    // Blank the used portion of the screen
    display_fillRect(x_fourth, 0, x_fourth, y_max, DISPLAY_BLACK);
    btn2_status = BUTTONS_NOT_SET;
  }

  // If BTN 3 is pressed
  if (buttons & BUTTONS_BTN3_MASK) {
    // Only draw image once
    if (btn3_status == BUTTONS_NOT_SET) {
      // Draw the background colored rectangle
      display_fillRect(0, 0, x_fourth, y_max, DISPLAY_RED);

      // Print BTN text in the middle of the rectangle
      display_setCursor(0, y_half); // set cursor to middle of rect
      display_println(" BTN 3");

      // Mark the button as SET to eliminate flickering
      btn3_status = BUTTONS_SET; // mark btn3 as set
    }
  }
  else {
    // Blank the used portion of the screen
    display_fillRect(0, 0, x_fourth, y_max, DISPLAY_BLACK);
    btn3_status = BUTTONS_NOT_SET;
  }
}

//*********************** End Helper Functions ********************************

int buttons_init() {
  int status = BUTTONS_INIT_STATUS_FAIL;  // Initialize as FAIL

  //write 1s to the tri-state driver to set buttons as input
  buttons_writeGpioRegister(BUTTONS_TRISTATE_OFFSET, BUTTONS_TRISTATE_SET_AS_INPUT);

  status = BUTTONS_INIT_STATUS_OK; // Set status to OK
  return status;
}

int32_t buttons_read() {

  // Read the value of the buttons
  int32_t registerValue = buttons_readGpioRegister(BUTTONS_VALUE_OFFSET);

  // Zero out all values but the bottom 4
  registerValue = registerValue & BUTTONS_BOTTOM_4_BITS;

  return registerValue;
}

void buttons_runTest() {
  buttons_init();  // Initialize buttons
  display_init();  // Initialize display, which sets Rotation = 1 by default
  display_fillScreen(DISPLAY_BLACK); // blank the screen
  display_setTextColor(DISPLAY_BLACK);  // Change text color to black
  display_setTextSize(BUTTONS_TEXT_SIZE); // Make text larger

  // Set the values of the global variables
  x_max = display_width();
  y_max = display_height();

  // Set the values of screen positions
  x_fourth = FOURTH(x_max);
  x_half = HALF(x_max);
  x_three_fourths = THREE_FOURTHS(x_max);
  y_fourth = FOURTH(y_max);
  y_half = HALF(y_max);
  y_three_fourths = THREE_FOURTHS(y_max);

  // Do an initial read of button values
  int32_t buttonValues = buttons_read();

  // Until all 4 BTNS are pressed simultaneously, write info to the LCD
  while (buttonValues != BUTTONS_ALL_BTNS_ON) {

    // Draw the Rects/Text on the LCD corresponding to current buttons
    buttons_write_LCD(buttonValues);

    // Poll new value of buttons
    buttonValues = buttons_read();
  }

  // After all buttons are pushed simultaneously, finish test.
  display_fillScreen(DISPLAY_BLACK);  // blank screen
  display_setTextColor(DISPLAY_CYAN); // change text color
  display_setCursor(0,0);  // reset cursor to origin
  display_println("Button Test Finished!");  // print that the test is complete
}
