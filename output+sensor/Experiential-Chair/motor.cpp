#include "motor.h"
#include "motor-array.h"
#include <Arduino.h>

void VibrationMotor::setup(int pin) {
    pinMode(pin, OUTPUT);
    this->MotorPin = pin;
}

void VibrationMotor::SequenceFire(int sequenceNumber) {
   self->startTime = millis();
   self->sequenceNumber = sequenceNumber;
}

void VibrationMotor::Sequence() {
   analogWrite(motor_array.sample(self->sequenceNumber, millis() - self->startTime ))
}
