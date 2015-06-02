#include "unity.h"
#include "LedModel.h"
#include "mock_LedHardware.h"
#include "mock_LedConductor.h"
#include "mock_leds.h"
#include "mock_intervalTimer.h"

void setup() {

}

void tearDown() {

}

void testInitShouldCallintervalTimer_initAll() {

  LedModel_Init();
}

void testgenerateSequenceShouldReturnRandomSequences() {
  int i;

  uint32_t  testSequence1[LEDMODEL_SEQUENCE_LENGTH] =
            {3, 2, 1, 3, 1, 3, 2, 0, 1, 1};
  uint32_t  testSequence2[LEDMODEL_SEQUENCE_LENGTH] =
            {2, 3, 0, 3, 1, 2, 0, 1, 1, 3};
  uint32_t  testSequence3[LEDMODEL_SEQUENCE_LENGTH] =
            {2, 1, 0, 0, 1, 0, 0, 0, 1, 0};
  uint32_t  testSequence4[LEDMODEL_SEQUENCE_LENGTH] =
            {1, 3, 2, 2, 3, 1, 1, 3, 0, 1};

  uint32_t* sequence;

  sequence = LedModel_generateSequence(1);
  for (i = 0; i < LEDMODEL_SEQUENCE_LENGTH; i++) {
    TEST_ASSERT_EQUAL(sequence[i], testSequence1[i]);
  }

  sequence = LedModel_generateSequence(2);
  for (i = 0; i < LEDMODEL_SEQUENCE_LENGTH; i++) {
    TEST_ASSERT_EQUAL(sequence[i], testSequence2[i]);
  }

  sequence = LedModel_generateSequence(3);
  for (i = 0; i < LEDMODEL_SEQUENCE_LENGTH; i++) {
    TEST_ASSERT_EQUAL(sequence[i], testSequence3[i]);
  }

  sequence = LedModel_generateSequence(4);
  for (i = 0; i < LEDMODEL_SEQUENCE_LENGTH; i++) {
    TEST_ASSERT_EQUAL(sequence[i], testSequence4[i]);
  }
}
