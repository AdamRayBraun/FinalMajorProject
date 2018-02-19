#include "motor.h"

VibrationMotor::VibrationMotor() {
    pinMode(this->MotorPin, OUTPUT);
}

VibrationMotor::~VibrationMotor(){
}

void VibrationMotor::ToggleStrength(int newStrength) {
    if (newStrength > 153) {
        newStrength = 153;
        Serial.println("ERR: strength over 153 sent to motor");
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
                        int pulseDelay)
                        {
    analogWrite(MotorPin, pulseStrength);
    delay(pulseDelay);
}

void VibrationMotor::GetStrength() {
    return (this->strength);
}
