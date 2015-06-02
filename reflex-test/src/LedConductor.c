/*
 * LedConductor.c
 *
 *  Created on: Jun 1, 2015
 *      Author: travis
 */

#include "LedConductor.h"
#include "LedModel.h"
#include "LedHardware.h"

void LedConductor_Init() {

  LedModel_Init();
  LedHardware_Init();
}

void LedConductor_Run() {

}


