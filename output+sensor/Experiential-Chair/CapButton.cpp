#include <CapacitiveSensor.h>
#include "CapButton.h"
#include <Arduino.h>

CapButton::CapButton(CapacitiveSensor *capacitiveSensor, int sendPin, int recievePin, int threshold) {
    this->capacitive_sensor = capacitiveSensor;
    this->threshold = threshold;
}

bool CapButton::CapacitiveSensing() {

    if (this->rawInput > this->threshold) {
      this->reading = true;
    } else {
      this->reading = false;
    }

    if (this->reading != this->lastButtonState) {
      this->lastDebounceTime = millis();
    }

    if ((millis() - this->lastDebounceTime) > this->debounceDelay) {
      if (this->reading != this->buttonState) {
        this->buttonState = this->reading;
        Serial.print("BUTTON PRESSED");
      }
    }

    return(this->buttonState);

    this->lastButtonState = this->reading;

}
