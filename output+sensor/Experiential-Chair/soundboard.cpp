#include "soundboard.h"
#include <Arduino.h>

// Library for triggering sounds with adafruit soundboard
// Trigger pins start sound when pulled to ground
// functions pull desired pin to ground and set all others HIGH

void SoundBoard::setup(int pin[]) {
  pinMode(RST_Pin, OUTPUT);
  this->RST_Pin = pin[0];

  for (x=1; x<11; x++) {
    pinMode(pin[x], OUTPUT);
    this->TriggerPins[x] = pin[x];
  }
}

void SoundBoard::sound(int trigger) {
  for (x= 0; x<=11; x++) {
    if (x == trigger) {
      digitalWrite(x, LOW);
    } else {
      digitalWrite(x, HIGH);
    }
  }
}

void SoundBoard::reset() {
  for (x= 0; x<=11; x++) {
    digitalWrite(x, HIGH);
  }
  digitalWrite(this->RST_Pin, LOW);
}
