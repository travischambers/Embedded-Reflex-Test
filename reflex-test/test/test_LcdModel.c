#include "unity.h"
#include "LcdModel.h"
#include "mock_ReflexTestData.h"

/**
 * This LCD is not testable by Ceedling because the Adafruit touchscreen
 * support code is written in C++
 */


 void setup() {

 }

 void tearDown() {

 }

 void testLcdModel_DisplayIgnoreMessage() {
   TEST_IGNORE_MESSAGE( "This test is ignore because the Adafruit Touchscreen"
                        " uses C++ support files, which are unsupported.");
 }
