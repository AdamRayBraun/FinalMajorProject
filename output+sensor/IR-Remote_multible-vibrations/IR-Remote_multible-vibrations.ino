#include "IRLibAll.h"
#include "motor.h"
#include "motor.cpp"

/// Dont forget counting starts at 0!!!
const int total_motors = 4;

// initiate motors passing each motor's pin
VibrationMotor motors[total_motors];

// IR remote set up
IRrecvPCI myReceiver(2);
IRdecode myDecoder;

// Processing communication
bool PROCESSING_DATA_VIS = false;
char processing_command;

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo

  // for communication with processing
  if (PROCESSING_DATA_VIS == true) {
      establishContact();
  }

  myReceiver.enableIRIn(); // Start the receiver

  motors[0].MotorPin = 3;
  motors[1].MotorPin = 5;
  motors[2].MotorPin = 6;
  motors[3].MotorPin = 9;
  motors[4].MotorPin = 10;

}

void loop() {
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {
    myDecoder.decode();           //Decode it
    if (myDecoder.protocolNum == NEC) {
        switch(myDecoder.value) {
            case 0xFF30CF:
                // button 1 on remote
                shortPositive();
                break;
            case 0xFF18E7:
                // button 2 on remote
                shortNegative();
                break;
            case 0xFF7A85:
                // button 3 on remote
                longPositive();
                break;
            case 0xFF10EF:
                // button 4 on remote
                longNegative();
                break;
        }
    }
    myReceiver.enableIRIn(); //Restart receiver
  }
}

void shortPositive() {
    Serial.println("1 pressed");

    for (int x = 0; x <= total_motors; x++) {
        motors[x].ToggleStrength(153);
    }
    delay(2000);
    for (int x = 0; x <= total_motors; x++) {
        motors[x].ToggleStrength(0);
    }
}

void shortNegative() {
    Serial.println("2 pressed");
}

void longPositive() {
    Serial.println("3 pressed");
}

void longNegative() {
    Serial.println("4 pressed");
}

// establish data contact with processing_command
void establishContact() {
    while (Serial.available() <= 0) {
        Serial.println("A");
        delay(300);
    }
}
