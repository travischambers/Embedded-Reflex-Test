#include "ButtonConductor.h"
#include "ButtonHardware.h"
#include "ButtonModel.h"
#include "buttons.h"

#include <stdint.h>
#include <stdio.h>
void ButtonConductor_Init() {
  ButtonModel_Init();
  ButtonHardware_Init();
}

void ButtonConductor_Run() {

  int32_t pressedButton = 0;

  // state actions
  switch (ButtonModel_GetCurrentState()) {
    case init_st:
      break;
    case show_info_st:
      break;
    case wait_info_st:
      //printf("in wait info state. reading buttons");
      pressedButton = ButtonHardware_Read();
      if (pressedButton != 0)
        printf("pressedButton = %d\n", pressedButton);
      ButtonModel_SetPressedButton(pressedButton);
      break;
    case wait_five_seconds_st:
      pressedButton = ButtonHardware_Read();
      ButtonModel_SetPressedButton(pressedButton);
      break;
    case blank_screen_st:
      break;
    case wait_between_flash_st:
      break;
    case blink_led_st:
      break;
    case wait_for_button_st:
      pressedButton = ButtonHardware_Read();
      ButtonModel_SetPressedButton(pressedButton);
      break;
    case button_pressed_st:
      break;
    case show_stats_st:
      break;
    case wait_stats_st:
      break;
    case update_scores_st:
      break;
  }

}
