#include "CapButton.h"
#include <Arduino.h>

CapButton::CapButton(int threshold)
  : threshold(threshold)
{ }

void CapButton::Service(long rawInput) {

    this->rawInput = rawInput;

    if (this->rawInput > this->threshold) {
      this->reading = true;
    } else {
      this->reading = false;
    }

    if (this->reading != this->lastReadingState) {
      this->lastDebounceTime = millis();
    }

    if ((millis() - this->lastDebounceTime) > this->debounceDelay) {
        if (this->reading != this->buttonState) {
          this->buttonState = this->reading;
        }
    }
    this->lastReadingState = this->reading;
}

bool CapButton::buttonValue() {
    return(this->buttonState);
}
