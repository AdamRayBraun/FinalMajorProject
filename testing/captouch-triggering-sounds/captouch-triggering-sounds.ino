#include <CapacitiveSensor.h>

// Capacitive buttons
const int numberOfCapButtons = 3;
CapacitiveSensor   CT0 = CapacitiveSensor(22,24);
CapacitiveSensor   CT1 = CapacitiveSensor(26,28);
CapacitiveSensor   CT2 = CapacitiveSensor(30,32);
CapacitiveSensor   CT3 = CapacitiveSensor(34,36);
bool buttonReading[numberOfCapButtons];
bool buttonState[numberOfCapButtons];
bool lastButtonState[numberOfCapButtons];
unsigned long lastDebounceTime[numberOfCapButtons];
unsigned long debounceDelay = 200;
long rawButtInput[numberOfCapButtons];

// Sound board
// Trigger pins for both soundboards
// int SB_SUB[] = {42,40,38,36,34,32,30,28,26,24,22};
// int SB_SUB_RST = 44;
int SB_BONE[] = {29,31,33,35,37,39,41,43,45,47,49};
int SB_BONE_RST = 27;

void setup() {
   Serial.begin(9600);

   // CAP BUTTONS
   // ground plane to help capacitive buttons stability
   pinMode(4, OUTPUT);
   digitalWrite(4, LOW);
   for (int x =0; x <= numberOfCapButtons; x++) {
     lastButtonState[x] = false;
   }


   // SOUND OUTPUT
   // set all soundboard pins as outputs
   pinMode(SB_BONE_RST, OUTPUT);
   for (int x=0; x<11; x++) {
     pinMode(SB_BONE[x], OUTPUT);
     digitalWrite(SB_BONE[x], HIGH);
   }
   soundTriggerReset();
}

void loop() {

    // read capcaitive touch buttons
    rawButtInput[0] =  CT0.capacitiveSensor(100);
    rawButtInput[1] =  CT1.capacitiveSensor(100);
    rawButtInput[2] =  CT2.capacitiveSensor(100);
    rawButtInput[3] =  CT3.capacitiveSensor(100);

    for (int button = 0; button <= numberOfCapButtons; button++) {
      if (rawButtInput[button] > 1400) {
        soundTrigger(button);
        // debounceButton(button);
      }
    }

    delay(10);        // arbitrary delay to limit data to serial port
}
void debounceButton(int button) {

    Serial.print("button: ");
    Serial.println(button);
    delay(1000);
}

void soundTrigger(int soundNumber) {
  // turn off last pin and trigger passed sound
  digitalWrite(SB_BONE[soundNumber], LOW);
  delay(300);
  digitalWrite(SB_BONE[soundNumber], HIGH);
  delay(1000); // for debouncing
}

void soundTriggerReset() {
  // turn off last pin and trigger RESET pin
  digitalWrite(SB_BONE_RST, LOW);
  delay(300);
  digitalWrite(SB_BONE_RST, HIGH);
}
