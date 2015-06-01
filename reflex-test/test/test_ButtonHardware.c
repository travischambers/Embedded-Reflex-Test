#include "unity.h"
#include "ButtonHardware.h"
#include "mock_ButtonModel.h"
#include "mock_ButtonConductor.h"
#include "mock_buttons.h"

void testButtonHardware_Init(void) {

 buttons_init_ExpectAndReturn(1);

 ButtonHardware_Init();
}
