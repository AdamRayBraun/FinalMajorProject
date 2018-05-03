// SoundBoard class for triggering individual sounds

#ifndef SoundBoard_h
#define SoundBoard_h

#include <Arduino.h>

class SoundBoard {
    public:
      int RST_pin;
      int TriggerPins[];
      void setup(int pin[]);
      void sound(int trigger);
      void reset();
    private:
};

#endif
