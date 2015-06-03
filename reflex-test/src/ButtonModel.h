#ifndef BUTTONMODEL_H_
#define BUTTONMODEL_H_

#include <stdint.h>

void ButtonModel_Init(void);
void ButtonModel_SetPressedButton(int32_t value);
void ButtonModel_SetResponseTime(double time);

#endif //BUTTONMODEL_H_
