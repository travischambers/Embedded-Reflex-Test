/*
 * LedConductor.c
 *
 *  Created on: Jun 1, 2015
 *      Author: travis
 */

#include "LedConductor.h"
#include "LedModel.h"
#include "LedHardware.h"
#include "intervalTimer.h"

void LedConductor_Init() {

  LedModel_Init();
  LedHardware_Init();
  intervalTimer_initAll();
  intervalTimer_start(INTERVALTIMER_TIMER0);
}

void LedConductor_Run() {

  int32_t ledNumber = 0;

      if (!LedModel_IsSequenceDone()) {
        ledNumber = LedModel_GetNextLed();
        LedHardware_Flash(ledNumber);
      }
}


