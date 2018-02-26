#include "motor.h"
#include <Arduino.h>

// VibrationMotor::VibrationMotor() {
//     pinMode(this->MotorPin, OUTPUT);
// }

long startTime;

void VibrationMotor::setup(int pin) {
    pinMode(pin, OUTPUT);
    this->MotorPin = pin;
}

void VibrationMotor::update() {
    if (this->currentFunction == "pulse") {
        // turns motor off after length of pulse
        if ((millis() - startTime) >= this->LengthOfPulse) {
            analogWrite(MotorPin, 0);
            this->strength = 0;
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
    startTime = millis();

    analogWrite(MotorPin, pulseStrength);
}

void VibrationMotor::GetStrength() {
    return (this->strength);
}
