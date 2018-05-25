// Motor class for vibration

#ifndef CapButton_h
#define CapButton_h

#include <CapacitiveSensor.h>
#include <Arduino.h>

class CapButton {
    public:
      CapButton(CapacitiveSensor capacitiveSensor, int sendPin, int recievePin, int threshold);
      void Service(long rawInput);
      bool buttonValue();

    private:
      CapacitiveSensor capacitiveSensor;
      
      long rawInput;
      int threshold;
      int sendPin;
      // debouncing variables
      bool reading = false;
      bool buttonState = false;
      bool lastReadingState = false;
      unsigned long lastDebounceTime = 0;
      unsigned long debounceDelay = 100;
};

#endif
