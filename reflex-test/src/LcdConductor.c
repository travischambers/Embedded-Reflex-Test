/*
 * LcdConductor.c
 *
 *  Created on: Jun 3, 2015
 *      Author: travis
 */

#include "LcdConductor.h"
#include "LcdHardware.h"
#include "LcdModel.h"

void LcdConductor_Init() {
  LcdModel_Init();
  LcdHardware_Init();
}

void LcdConductor_Run() {

}

