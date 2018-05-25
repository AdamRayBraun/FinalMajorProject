#include <CapacitiveSensor.h>
#include "CapButton.h"
#include <Arduino.h>

CapButton::CapButton(int sendPin, int recievePin, int threshold)
  : threshold(threshold),
    sendPin(sendPin)
{ }

void CapButton::Service(long rawInput) {
#if 1
    this->rawInput = rawInput; //this->capacitive_sensor.capacitiveSensor(100);

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
