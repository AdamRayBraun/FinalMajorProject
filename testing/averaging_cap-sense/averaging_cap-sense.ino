#include <CapacitiveSensor.h>

const long numReadings = 10;

long readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
long total = 0;                  // the running total
long average = 0;                // the average

// const long 2numReadings = 10;
//
// long 2readings[2numReadings];      // the readings from the analog input
// int 2readIndex = 0;              // the index of the current reading
// long 2total = 0;                  // the running total
// long 2average = 0;                // the average

CapacitiveSensor   CapButton1 = CapacitiveSensor(4,3);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
// CapacitiveSensor   CapButton2 = CapacitiveSensor(4,3);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil

void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
  // initialize all the readings to 0:
  for (long thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  // for (long 2thisReading = 0; 2thisReading < 2numReadings; 2thisReading++) {
  //   2readings[2thisReading] = 0;
  // }
}


void loop() {

  long total1 =  CapButton1.capacitiveSensor(30);
  // long total2 =  CapButton2.capacitiveSensor(30);

  // subtract the last reading:
  total = total - readings[readIndex];
  // 2total = 2total - 2readings[2readIndex];
  // read from the sensor:
  readings[readIndex] = total1;
  // 2readings[2readIndex] = total2
  // add the reading to the total:
  total = total + readings[readIndex];
  // 2total = 2total + 2readings[2readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;
  // 2readIndex = 2readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  // if (2readIndex >= 2numReadings) {
  //   // ...wrap around to the beginning:
  //   2readIndex = 0;
  // }

  // calculate the average:
  average = total / numReadings;
  // 2average = 2total / 2numReadings;

  Serial.print("button 1:");
  Serial.print("    ");
  Serial.println(average);
  // Serial.print("button 2:");
  // Serial.print("    ");
  // Serial.println(2average);
  delay(1);        // delay in between reads for stability
}
