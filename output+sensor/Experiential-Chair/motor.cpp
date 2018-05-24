#include "motor.h"
#include "motor_array.h"
#include <Arduino.h>

VibrationMotor::VibrationMotor(MotorSequence *motorSequence, int pin, bool debug) {
    pinMode(pin, OUTPUT);
    this->MotorPin = pin;
    this->motor_sequence = motorSequence;
    this->debugPrinting = debug;
}

void VibrationMotor::SequenceFire(int sequenceNumber) {
   this->startTime = millis();
   this->sequenceNumber = sequenceNumber;
}

void VibrationMotor::Sequence() {
   long timeDifference = millis() - this->startTime;
   int vibrationStrength = motor_sequence->sample(
                  this->sequenceNumber,
                  timeDifference);
   analogWrite(this->MotorPin, vibrationStrength);

   if (this->debugPrinting == true) {
     Serial.print("Motor Number: ");
     Serial.print("\t");
     Serial.print(this->MotorPin);
     Serial.print("  Sequence: ");
     Serial.print(this->sequenceNumber);
     Serial.print("\t");
     Serial.print("Sequence Position:  ");
     Serial.print(timeDifference);
     Serial.print("Motor Strength:   ");
     Serial.println(vibrationStrength);
   }
}
