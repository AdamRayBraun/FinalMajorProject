#include "motor_array.h"
#include <Arduino.h>


uint8_t MotorSequence::sample(int sequenceNumber, unsigned long offset) {

    int sequenceStep = offset / this->sampleLength;

    int sequenceLength =
      (sizeof(this->sequence[sequenceNumber])/sizeof(uint8_t));
    if (sequenceStep < sequenceLength) {
      return(this->sequence[sequenceNumber][sequenceStep]);
    }
    else {
      return(0);
    }
}
