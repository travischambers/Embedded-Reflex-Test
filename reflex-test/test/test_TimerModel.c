#include "unity.h"
#include "TimerModel.h"
#include "ReflexTestData.h"

void setup() {

}

void tearDown() {

}

void testTimerModel_ShouldBeAbleToRecordResponseTimesAndCalculateCorrectly() {
  TimerModel_ClearOldStats();
  ReflexTestData_Init();

  // Save a sequence of 10 "reponse times"
  TimerModel_RecordResponseTime(0.2);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.1);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.1);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.1);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.1);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.1);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.1);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.1);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.1);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.1);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.9);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_CalculateStats();

  TEST_ASSERT_EQUAL(0.1, TimerModel_GetMin());
  TEST_ASSERT_EQUAL(0.9, TimerModel_GetMax());
  TEST_ASSERT_EQUAL(0.19, TimerModel_GetAverage());

  TimerModel_ClearOldStats();
  ReflexTestData_Init();

  // Save a sequence of 10 "reponse times"
  TimerModel_RecordResponseTime(0.3);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.3);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.3);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.3);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.3);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.3);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.3);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.3);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.3);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.3);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_RecordResponseTime(0.3);
  ReflexTestData_IncrementIndex(); // increment index

  TimerModel_CalculateStats();

  TEST_ASSERT_EQUAL(0.3, TimerModel_GetMin());
  TEST_ASSERT_EQUAL(0.3, TimerModel_GetMax());
  TEST_ASSERT_EQUAL(0.3, TimerModel_GetAverage());
}
