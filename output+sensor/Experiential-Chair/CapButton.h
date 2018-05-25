// Motor class for vibration

#ifndef CapButton_h
#define CapButton_h

#include <Arduino.h>

class CapButton {
    public:
      CapButton(int threshold);
      void Service(long rawInput);
      bool buttonValue();

    private:
      long rawInput;
      int threshold;

      // debouncing variables
      bool reading = false;
      bool buttonState = false;
      bool lastReadingState = false;
      unsigned long lastDebounceTime = 0;
      unsigned long debounceDelay = 100;
};

#endif
