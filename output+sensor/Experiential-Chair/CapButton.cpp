#include <CapacitiveSensor.h>
#include "CapButton.h"
#include <Arduino.h>

CapButton::CapButton(CapacitiveSensor capacitiveSensor, int sendPin, int recievePin, int threshold)
  : capacitiveSensor(capacitiveSensor),
    threshold(threshold),
    sendPin(sendPin)
{ }

void CapButton::Service(long rawInput) {
#if 1
    this->rawInput = this->capacitiveSensor.capacitiveSensor(100);

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
          Serial.print("BUTTON PRESSED: ");
          Serial.println(this->sendPin);
        }
    }
    this->lastReadingState = this->reading;
#endif
}

bool CapButton::buttonValue() {
    return(this->buttonState);
}
