/*
 * TimerHardware.h
 *
 *  Created on: Jun 3, 2015
 *      Author: travis
 */

#ifndef TIMERHARDWARE_H_
#define TIMERHARDWARE_H_


void TimerHardware_Init(void);
double TimerHardware_GetResponseTime(void);
void TimerHardware_StopTimer(void);
void TimerHardware_StartTimer(void);

#endif /* TIMERHARDWARE_H_ */
