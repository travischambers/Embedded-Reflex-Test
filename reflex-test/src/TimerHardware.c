/*
 * TimerHardware.c
 *
 *  Created on: Jun 3, 2015
 *      Author: travis
 */

#include "TimerHardware.h"
#include "ReflexTestData.h"
#include "intervalTimer.h"

double TimerHardware_GetResponseTime() {
    double responseTime;
    intervalTimer_getTotalDurationInSeconds(INTERVALTIMER_TIMER0, &responseTime);
    return responseTime;
}

void TimerHardware_StopTimer() {
  intervalTimer_stop(INTERVALTIMER_TIMER0);
}

void TimerHardware_StartTimer() {
  intervalTimer_start(INTERVALTIMER_TIMER0);
}
