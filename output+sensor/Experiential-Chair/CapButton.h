// Motor class for vibration

#ifndef CapButton_h
#define CapButton_h

#include <Arduino.h>

class CapButton {
    public:
      CapButton(CapacitiveSensor *capacitiveSensor, int sendPin, int recievePin, int threshold);
      bool CapacitiveSensing();

    private:
      long rawInput;
      int threshold;
      CapacitiveSensor *capacitive_sensor;
      // debouncing variables
      bool reading = false;
      bool buttonState = false;
      bool lastButtonState = false;
      unsigned long lastDebounceTime = 0;
      unsigned long debounceDelay = 100;
};

#endif
