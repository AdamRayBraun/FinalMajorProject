#include "IRLibAll.h"

struct motor {
    int pin;
};

// Value 0 = GPIO pin
struct motor MotorData[] = {{ 3 },
                            { 5 },
                            { 6 },
                            { 9 },
                            { 10 }
                        };


IRrecvPCI myReceiver(2);
IRdecode myDecoder;

// Processing communication
bool PROCESSING_DATA_VIS = false;
char processing_command;

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo

  if (PROCESSING_DATA_VIS == true) {
      establishContact();
  }

  myReceiver.enableIRIn(); // Start the receiver

  for (int x = 0; x < 5; x++) {
      pinMode(MotorData[x].pin, OUTPUT);
  };
}

void loop() {
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {
    myDecoder.decode();           //Decode it
    if (myDecoder.protocolNum == NEC) {
        switch(myDecoder.value) {
            case 0xFF30CF:
                shortPositive();
                break;
            case 0xFF18E7:
                shortNegative();
                break;
            case 0xFF7A85:
                longPositive();
                break;
            case 0xFF10EF:
                longNegative();
                break;
        }
    }
    myReceiver.enableIRIn(); //Restart receiver
  }
}

void shortPositive() {
    Serial.println("1 pressed");

    for (int x = 0; x < 5; x++) {
        Serial.println("Pulse sent to motor: " + x);
        analogWrite(MotorData[x].pin, 153);
        delay(2000);
        analogWrite(MotorData[x].pin, 0);
        delay(1000);
    }
}

void shortNegative() {
    Serial.println("2 pressed");

    for (int x = 0; x < 5; x++) {
        Serial.println("Pulse sent to motor: " + x);
        analogWrite(MotorData[x].pin, 255);
        delay(2000);
        analogWrite(MotorData[x].pin, 0);
        delay(1000);
    }
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
