// Motor class for vibration animation

#ifndef motor_h
#define motor_h

#include <Arduino.h>

class VibrationMotor {
    public:
        void setup(int pin);
        void SequenceFire(int sequenceNumber);
        void Sequence();
    private:
      unsigned long startTime;
      int sequenceNumber;
};

#endif
