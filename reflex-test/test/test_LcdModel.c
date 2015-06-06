#include "unity.h"
#include "LcdModel.h"
#include "mock_ReflexTestData.h"

 void setup() {

 }

 void tearDown() {

 }

void testLcdModel_GetCurrentStateReturnsStateFromReflexTestData() {
  ReflexTest_st currentState;

  ReflexTestData_GetCurrentState_ExpectAndReturn(init_st);
  currentState = LcdModel_GetCurrentState();
  TEST_ASSERT_EQUAL(init_st, currentState);

  ReflexTestData_GetCurrentState_ExpectAndReturn(show_info_st);
  currentState = LcdModel_GetCurrentState();
  TEST_ASSERT_EQUAL(show_info_st, currentState);

  ReflexTestData_GetCurrentState_ExpectAndReturn(blink_led_st);
  currentState = LcdModel_GetCurrentState();
  TEST_ASSERT_EQUAL(blink_led_st, currentState);

  ReflexTestData_GetCurrentState_ExpectAndReturn(show_stats_st);
  currentState = LcdModel_GetCurrentState();
  TEST_ASSERT_EQUAL(show_stats_st, currentState);

  ReflexTestData_GetCurrentState_ExpectAndReturn(update_scores_st);
  currentState = LcdModel_GetCurrentState();
  TEST_ASSERT_EQUAL(update_scores_st, currentState);
}

void testLcdModel_GetAverageResponseTimePullsDataFromReflexTestData() {
  double average = 0.0;

  ReflexTestData_GetAverageResponseTime_ExpectAndReturn(1.123);
  average = LcdModel_GetAverageResponseTime();
  TEST_ASSERT_EQUAL(1.123, average);

  ReflexTestData_GetAverageResponseTime_ExpectAndReturn(8.001);
  average = LcdModel_GetAverageResponseTime();
  TEST_ASSERT_EQUAL(8.001, average);

  ReflexTestData_GetAverageResponseTime_ExpectAndReturn(7.0);
  average = LcdModel_GetAverageResponseTime();
  TEST_ASSERT_EQUAL(7.0, average);
}

void testLcdModel_GetMinResponseTimePullsDataFromReflexTestData() {
  double min = 0.0;

  ReflexTestData_GetMinResponseTime_ExpectAndReturn(0.123);
  min = LcdModel_GetMinResponseTime();
  TEST_ASSERT_EQUAL(0.123, min);

  ReflexTestData_GetMinResponseTime_ExpectAndReturn(1.189);
  min = LcdModel_GetMinResponseTime();
  TEST_ASSERT_EQUAL(1.189, min);

  ReflexTestData_GetMinResponseTime_ExpectAndReturn(7.0);
  min = LcdModel_GetMinResponseTime();
  TEST_ASSERT_EQUAL(7.0, min);
}

void testLcdModel_GetMaxResponseTimePullsDataFromReflexTestData() {
  double max = 0.0;

  ReflexTestData_GetMaxResponseTime_ExpectAndReturn(0.123);
  max = LcdModel_GetMaxResponseTime();
  TEST_ASSERT_EQUAL(0.123, max);

  ReflexTestData_GetMaxResponseTime_ExpectAndReturn(1.189);
  max = LcdModel_GetMaxResponseTime();
  TEST_ASSERT_EQUAL(1.189, max);

  ReflexTestData_GetMaxResponseTime_ExpectAndReturn(7.0);
  max = LcdModel_GetMaxResponseTime();
  TEST_ASSERT_EQUAL(7.0, max);
}

void testLcdModel_GetHighScoresShouldReturnAPointerToAnArrayOfDoubles() {
  double* address;
  ReflexTestData_GetHighScores_ExpectAndReturn((double *)0xDEADBEEF);
  address = LcdModel_GetHighScores();
  TEST_ASSERT_EQUAL(0xDEADBEEF, address);

  ReflexTestData_GetHighScores_ExpectAndReturn((double *)0x10203040);
  address = LcdModel_GetHighScores();
  TEST_ASSERT_EQUAL(0x10203040, address);

  ReflexTestData_GetHighScores_ExpectAndReturn((double *)0x12341234);
  address = LcdModel_GetHighScores();
  TEST_ASSERT_EQUAL(0x12341234, address);
}
