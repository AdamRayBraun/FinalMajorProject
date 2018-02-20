#include "IRLibAll.h"
#include "motor.h"

// TODO should recognise if serial connection is lost so it tries to establish
// connection again


/// Dont forget counting starts at 0!!!
const int total_motors = 4;

// initiate motors passing each motor's pin
VibrationMotor motors[total_motors];

// IR remote set up
IRrecvPCI myReceiver(2);
IRdecode myDecoder;

// Processing communication
bool PROCESSING_DATA_VIS = true;
char processing_command;


// loop Variables
unsigned long previousTime = 0;
int pulseLength = 2000;

String vibration = "none";

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
  motors[4].setup(10);
}

void loop() {
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {
    remoteHandler();
    }

  if (PROCESSING_DATA_VIS == true) {
    procesingHandler();
    }

  if (vibration != "none") {
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
    if (vibration == "shortPositive") {
        for (int x = 0; x <= total_motors; x++) {
            motors[x].update();
        }
    }
    else if (vibration == "shortNegative") {
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
            if (x != 4) {
                Serial.print(",");
            }
        }
        Serial.println(",");

        delay(50);
    }
}

void remoteHandler() {
    myDecoder.decode();           //Decode it
    if (myDecoder.protocolNum == NEC) {
        switch(myDecoder.value) {
            case 0xFF30CF:
                // button 1 on remote
                shortPositive();
                vibration = "shortPositive";
                break;
            case 0xFF18E7:
                // button 2 on remote
                vibration = "shortNegative";
                break;
            case 0xFF7A85:
                // button 3 on remote
                vibration = "longPositive";
                break;
            case 0xFF10EF:
                // button 4 on remote
                vibration = "longNegative";
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
