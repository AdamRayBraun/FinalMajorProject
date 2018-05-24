// Motor class for vibration

#ifndef motor_h
#define motor_h

#include "motor_array.h"
#include <Arduino.h>

class VibrationMotor {
    public:
        VibrationMotor(MotorSequence *motorSequence, int pin, bool debug);
        void SequenceFire(int sequenceNumber);
        void Sequence();
    private:
      bool debugPrinting;
      int MotorPin;
      unsigned long startTime;
      int sequenceNumber;
      MotorSequence *motor_sequence;
};

#endif
