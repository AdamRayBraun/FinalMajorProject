#include <CapacitiveSensor.h>

// Sound board
// Trigger pins for both soundboards
// int SB_SUB[] = {42,40,38,36,34,32,30,28,26,24,22};
// int SB_SUB_RST = 44;
int SB_BONE[] = {29,31,33,35,37,39,41,43,45,47,49};
int SB_BONE_RST = 27;


int REDbutt = 22;
int YELLOWbutt = 24;

void setup() {
   Serial.begin(9600);

   pinMode(REDbutt, INPUT_PULLUP);
   pinMode(YELLOWbutt, INPUT_PULLUP);

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

  int REDbuttVal = digitalRead(REDbutt);
  int YELLOWbuttVal = digitalRead(YELLOWbutt);

  if (REDbuttVal == LOW) {
    Serial.println("Red butt pressed");
    soundTrigger(0);
  } else if (YELLOWbuttVal == LOW) {
    Serial.println("Yellow butt pressed");
    soundTrigger(1);
  }

  delay(10);        // arbitrary delay to limit data to serial port
}
void debounceButton(int button) {
}

void soundTrigger(int soundNumber) {
  digitalWrite(SB_BONE[soundNumber], LOW);
  Serial.print("SOUND TRIGGERED: ");
  Serial.println(soundNumber);
  delay(300);
  digitalWrite(SB_BONE[soundNumber], HIGH);
  delay(1000); // for debouncing
}

void soundTriggerReset() {

  digitalWrite(SB_BONE_RST, LOW);
  delay(300);
  digitalWrite(SB_BONE_RST, HIGH);
}
