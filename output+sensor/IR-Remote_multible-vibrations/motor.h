// Motor class for vibration animation

#ifndef motor_h
#define motor_h

#include <Arduino.h>

class VibrationMotor {
    public:
        // VibrationMotor();
        int MotorPin;
        int strength;        // stores strength of each motor 0 - 153
        void setup(int pin);
        void ToggleStrength(int newStrength);
        void IncreaseVibration(
                        int startingStrength,
                        int endStrength,
                        int changeDelay);
        void DecreaseVibtration(
                        int startingStrength,
                        int endStrength,
                        int changeDelay);
        void Pulse(
                int pulseStrength,
                int pulseDelay);
        void GetStrength();

    private:
        int _MotorPin;
        int _strength;
};

#endif
