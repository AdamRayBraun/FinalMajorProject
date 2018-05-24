#include "motor.h"
#include "motor_array.h"

const int total_motors = 4;
int vibrationMode = 0;

VibrationMotor *motors[total_motors];
MotorSequence  *motorSequence;


void setup() {
  Serial.begin(9600);

  motorSequence = new MotorSequence();

  for (int x =0; x < total_motors; x++) {
    if (x == 0) {
      motors[x] = new VibrationMotor(motorSequence, 9+x, true);
    }
    else {
      motors[x] = new VibrationMotor(motorSequence, 9+x, false);
    }
  }

  for (int x = 0; x < total_motors; x++) {
    motors[x]->SequenceFire(0);
  }

}

void loop() {
  for (int x = 0; x < total_motors; x++) {
    motors[x]->Sequence();
  }

}

void shortPositive() {
  for (int x = 0; x < total_motors; x++) {
    motors[x]->SequenceFire(0);
  }

}

void shortNegative() {
  for (int x = 0; x < total_motors; x++) {
    motors[x]->SequenceFire(1);
  }
}

void longPositive() {
  for (int x = 0; x < total_motors; x++) {
    motors[x]->SequenceFire(2);
  }
}

void longNegative() {
  for (int x = 0; x < total_motors; x++) {
    motors[x]->SequenceFire(3);
  }
}
