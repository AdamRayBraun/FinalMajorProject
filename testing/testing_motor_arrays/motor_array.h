// Motor class for animation

#ifndef motor_array_h
#define motor_array_h

#include <Arduino.h>

class MotorSequence {
    public:
      uint8_t sample(int sequencenumber, unsigned long offset);
      uint8_t sequence[4][10] = {
          {135, 153,  153,  153,  153,  153,  153,  153,  153,  153},
          {0, 0,  0,  0,  0,  153,  153,  153,  153,  153},
          {0, 0,  0,  0,  0,  0,  0,  0,  0,  0},
          {0, 0,  0,  0,  0,  0,  0,  0,  0,  0}  };
    private:
      const int sampleLength = 100;
};

#endif
