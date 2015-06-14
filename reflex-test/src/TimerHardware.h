#ifndef TIMERHARDWARE_H_
#define TIMERHARDWARE_H_

/**
 * Initializes the interval timer hardware.
 */
void TimerHardware_Init(void);

/**
 * Returns the duration in seconds between the last start/stop of the timer.
 * @return  The elapsed time in sec between start/stop.
 */
double TimerHardware_GetResponseTime(void);

/**
 * Stops the interval timer.
 */
void TimerHardware_StopTimer(void);

/**
 * Starts the interval timer.
 */
void TimerHardware_StartTimer(void);

/**
 * Resets the interval timer to set it's start time to 0.0 sec.
 */
void TimerHardware_ResetTimer(void);

#endif /* TIMERHARDWARE_H_ */
