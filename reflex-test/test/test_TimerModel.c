#include "TimerModel.h"
#include "mock_ReflexTestData.h"

void setup() {

}

void tearDown() {

}

void testTimerModel_ShouldBeAbleToRecordResponseTimesAndCalculateCorrectly() {
  TimerModel_ClearOldStats();

  // Save a sequence of 10 "reponse times"
  TimerModel_RecordResponseTime(0.2);
  ReflexTestData_IncrementIndex_Expect(); // increment index

  TimerModel_RecordResponseTime(0.1);
  ReflexTestData_IncrementIndex_Expect(); // increment index

  TimerModel_RecordResponseTime(0.1);
  ReflexTestData_IncrementIndex_Expect(); // increment index

  TimerModel_RecordResponseTime(0.1);
  ReflexTestData_IncrementIndex_Expect(); // increment index

  TimerModel_RecordResponseTime(0.1);
  ReflexTestData_IncrementIndex_Expect(); // increment index

  TimerModel_RecordResponseTime(0.1);
  ReflexTestData_IncrementIndex_Expect(); // increment index

  TimerModel_RecordResponseTime(0.1);
  ReflexTestData_IncrementIndex_Expect(); // increment index

  TimerModel_RecordResponseTime(0.1);
  ReflexTestData_IncrementIndex_Expect(); // increment index

  TimerModel_RecordResponseTime(0.1);
  ReflexTestData_IncrementIndex_Expect(); // increment index

  TimerModel_RecordResponseTime(0.1);
  ReflexTestData_IncrementIndex_Expect(); // increment index

  TimerModel_RecordResponseTime(0.9);
  ReflexTestData_IncrementIndex_Expect(); // increment index

  TimerModel_CalculateStats();

  TEST_ASSERT_EQUAL(0.1, TimerModel_GetMin());
  TEST_ASSERT_EQUAL(0.9, TimerModel_GetMax());
  TEST_ASSERT_EQUAL(0.19, TimerModel_GetAverage());
}
