#include <CapacitiveSensor.h>
#include "CapButton.h"
#include <Arduino.h>

CapButton::CapButton(CapacitiveSensor *capacitiveSensor, int sendPin, int recievePin, int threshold) {
    this->threshold = threshold;
    this->capacitive_sensor = capacitiveSensor;
    capacitive_sensor->CapacitiveSensor(sendPin,recievePin);
}

bool CapButton::CapacitiveSensing() {
    this->rawInput = this->capacitive_sensor->capacitiveSensor(100);

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
