#ifndef _ButtonHardware_H
#define _ButtonHardware_H

#include <stdint.h>

void ButtonHardware_Init(void);
int32_t ButtonHardware_Read(void);
void ButtonHardware_StopTimer(void);
double ButtonHardware_GetResponseTime(void);

#endif //_ButtonHardware_H
