#include <CapacitiveSensor.h>

CapacitiveSensor   CapButton1 = CapacitiveSensor(6,5);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   CapButton2 = CapacitiveSensor(4,3);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil

int SB_SUB[] = {42,40,38,36,34,32,30,28,26,24,22};
int SB_SUB_RST = 44;
int SB_BONE[] = {29,31,33,35,37,39,41,43,45,47,49};
int SB_BONE_RST = 27;

const int numReadings = 20;

long readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

void setup()
{
   Serial.begin(9600);

   pinMode(SB_BONE_RST, OUTPUT);
   for (int x=0; x<11; x++) {
     pinMode(SB_BONE[x], OUTPUT);
   }

   for (int x=0; x<11; x++) {
     digitalWrite(SB_BONE[x], HIGH);
   }

   // initialize all the readings to 0:
   for (int thisReading = 0; thisReading < numReadings; thisReading++) {
     readings[thisReading] = 0;
   }
}

void loop()
{
    long start = millis();
    long total1 =  CapButton1.capacitiveSensor(30);
    long total2 =  CapButton2.capacitiveSensor(30);

    // subtract the last reading:
    total = total - readings[readIndex];
    // read from the sensor:
    readings[readIndex] = CapButton1.capacitiveSensor(30);
    // add the reading to the total:
    total = total + readings[readIndex];
    // advance to the next position in the array:
    readIndex = readIndex + 1;

    // if we're at the end of the array...
    if (readIndex >= numReadings) {
      // ...wrap around to the beginning:
      readIndex = 0;
    }

    // calculate the average:
    average = total / numReadings;


    if (total1 > 200) {
      soundTrigger(1);
      Serial.println("1 triggered");
    } else if (total2 > 200) {
      soundTrigger(2);
      Serial.println("2 triggered");
    }
    delay(10);                             // arbitrary delay to limit data to serial port
}

void soundTrigger(int soundNumber) {
  soundTriggerReset();

  digitalWrite(SB_BONE_RST, HIGH);

  for (int x=0; x<11; x++) {
    if (x != soundNumber) {
      digitalWrite(SB_BONE[x], HIGH);
    } else if (x == soundNumber) {
      digitalWrite(SB_BONE[x], LOW);
    }
  }
}

void soundTriggerReset() {
  for (int x=0; x<11; x++) {
    digitalWrite(SB_BONE[x], HIGH);
  }
  digitalWrite(SB_BONE_RST, LOW);
}
