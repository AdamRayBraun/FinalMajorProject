#include "IRLibAll.h"

//Create a receiver object to listen on pin 2
IRrecvPCI myReceiver(8);

//Create a decoder object
IRdecode myDecoder;

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
}

void loop() {
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {
    myDecoder.decode();           //Decode it
    if (myDecoder.protocolNum == NEC) {
        switch(myDecoder.value) {
            case 0xFF30CF:
                Serial.println("1 pressed");
                break;
            case 0xFF18E7:
                Serial.println("2 pressed");
                break;
            case 0xFF7A85:
                Serial.println("3 pressed");
                break;
            case 0xFF10EF:
                Serial.println("4 pressed");
                break;
        }
    }
    myReceiver.enableIRIn();      //Restart receiver
  }
}
