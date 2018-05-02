#include "IRLibAll.h"
#include "motor.h"

/* TODO
-should recognise if serial connection is lost so it tries to establish
  connection again
*/

/* VARIABLES TO SOMETIMES CHANGE */
/// Dont forget counting starts at 0!!!
const int total_motors = 3;

bool PROCESSING_DATA_VIS = false;

const int IR_pin = 8;

/* CONSTANT VARIABLES */
// initiate motors passing each motor's pin
VibrationMotor motors[total_motors];

// IR remote set up
IRrecvPCI myReceiver(IR_pin);
IRdecode myDecoder;

// Processing communication
char processing_command;

// loop Variables
unsigned long previousTime = 0;
int pulseLength = 2000;

int vibrationMode = 0;

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo

  // for communication with processing
  if (PROCESSING_DATA_VIS == true) {
      establishContact();
  }

  myReceiver.enableIRIn(); // Start the receiver

  // setup pinouts on each motor object
  motors[0].setup(3);
  motors[1].setup(5);
  motors[2].setup(6);
  motors[3].setup(9);
}

void loop() {
    // IR reciever
  if (myReceiver.getResults()) {
    remoteHandler();
    }

  if (PROCESSING_DATA_VIS == true) {
    procesingHandler();
    }
  else if (PROCESSING_DATA_VIS == false) {
      // printing straight to serial monitor for debugging

      Serial.println(vibrationMode);
  }

  if (vibrationMode != 0) {
      vibrationHandler();
    }
}


void shortPositive() {
    if (PROCESSING_DATA_VIS == false) {
        Serial.println("1 pressed");
    }
    for (int x = 0; x <= total_motors; x++) {
        motors[x].Pulse(153,2000);
    }
}

void shortNegative() {
    if (PROCESSING_DATA_VIS == false) {
        Serial.println("2 pressed");
    }
}

void longPositive() {
    if (PROCESSING_DATA_VIS == false) {
        Serial.println("3 pressed");
    }
}

void longNegative() {
    if (PROCESSING_DATA_VIS == false) {
        Serial.println("4 pressed");
    }
}

// handles different looping logic for each vibration
void vibrationHandler() {
    if (vibrationMode == 1) {
        for (int x = 0; x <= total_motors; x++) {
            motors[x].update();
        }
        // vibrationMode = 0;
    }
    else if (vibrationMode == 2) {
        for (int x = 0; x <= total_motors; x++) {
            if (motors[x].strength > 0) {
                motors[x].ToggleStrength(0);

                int next_motor = x + 1;
                if (next_motor >= total_motors){
                    next_motor -= total_motors;
                }
                motors[next_motor].ToggleStrength(153);

                break;
            }
        }
    }
    else if (vibrationMode == 4) {
        for (int x = 0; x <= total_motors; x++) {
            motors[x].ToggleStrength(0);
        }
        vibrationMode = 0;
    }
}

void procesingHandler() {
    // if data is available to read
    if (Serial.available() > 0) {
        processing_command = Serial.read();

        if (processing_command == '1') {
            ; // do something
        }
        delay(100);
    }
    // else send motor data
    else {
        for (int x = 0; x <= total_motors; x++) {
            Serial.print(motors[x].strength);
            Serial.print(",");
        }
        Serial.println(vibrationMode);

        delay(50);
    }
}

void remoteHandler() {
    myDecoder.decode();           //Decode it
    if (myDecoder.protocolNum == NEC) {
        switch(myDecoder.value) {
            case 0xFF30CF:
                // button 1 on remote
                vibrationMode = 1;
                shortPositive();
                break;
            case 0xFF18E7:
                // button 2 on remote
                vibrationMode = 2;
                break;
            case 0xFF7A85:
                // button 3 on remote
                vibrationMode = 3;
                break;
            case 0xFF10EF:
                // button 4 on remote
                vibrationMode = 4;
                break;
        }
    }
    myReceiver.enableIRIn(); //Restart IR receiver
}

// establish data contact with processing_command
void establishContact() {
    while (Serial.available() <= 0) {
        Serial.println("A");
        delay(300);
    }
}
