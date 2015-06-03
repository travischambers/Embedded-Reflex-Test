/*
 * TimerConductor.c
 *
 *  Created on: Jun 3, 2015
 *      Author: travis
 */

#include "TimerConductor.h"
#include "TimerHardware.h"
#include "TimerModel.h"

void TimerConductor_Init() {
  TimerHardware_Init();
  TimerModel_Init();
}

void TimerConductor_Run() {

}


