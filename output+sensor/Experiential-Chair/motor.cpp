#include "motor.h"
#include "motor_array.h"
#include <Arduino.h>

VibrationMotor::VibrationMotor(MotorSequence *motorSequence, int pin, bool debug)
  : MotorPin(pin),
    motor_sequence(motorSequence),
    debugPrinting(debug),
    sequenceNumber(0),
    startTime(0L)
 {
    pinMode(pin, OUTPUT);
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
     Serial.print("MOTOR Number: ");
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
