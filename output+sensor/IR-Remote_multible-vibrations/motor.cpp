#include "motor.h"
#include <Arduino.h>

// VibrationMotor::VibrationMotor() {
//     pinMode(this->MotorPin, OUTPUT);
// }

void VibrationMotor::setup(int pin) {
    pinMode(pin, OUTPUT);
    this->MotorPin = pin;
}

void VibrationMotor::update() {
    if (this->currentFunction == "pulse") {
        if ((millis() - this->startTime) >= this->LengthOfPulse) {
            analogWrite(MotorPin, this->PrePulseStrength);
            this->strength = this->PrePulseStrength;
            this->currentFunction = "none";
        }
    }
}

void VibrationMotor::ToggleStrength(int newStrength) {
    if (newStrength > 153) {
        newStrength = 153;
    }

    analogWrite(MotorPin, newStrength);
    this->strength = newStrength;
}

void VibrationMotor::IncreaseVibration(
                                int startingStrength,
                                int endStrength,
                                int changeDelay)
                                {
    for (int x = startingStrength; x < endStrength; x ++){
        analogWrite(MotorPin, x);
        this->strength = x;
        delay(changeDelay);
    }
}

void VibrationMotor::DecreaseVibtration(
                                int startingStrength,
                                int endStrength,
                                int changeDelay)
                                {
    for (int x = startingStrength; x < endStrength; x ++){
        analogWrite(MotorPin, x);
        this->strength = x;
        delay(changeDelay);
    }
}

void VibrationMotor::Pulse(
                        int pulseStrength,
                        int pulseLength)
                        {
    this->currentFunction = "pulse";
    this->PrePulseStrength = this->strength;
    this->LengthOfPulse = pulseLength;
    this->strength = pulseStrength;
    this->startTime = millis();

    analogWrite(MotorPin, pulseStrength);
}

void VibrationMotor::GetStrength() {
    return (this->strength);
}
