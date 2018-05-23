#include <CapacitiveSensor.h>

const long numReadings = 10;

const int C_numReadings = 10;

long C_readings[C_numReadings];    // the readings from the analog input
int  C_readIndex = 0;              // the index of the current reading
long C_total = 0;                  // the running total
long C_average = 0;                // the average

const int S_numReadings = 10;

long S_readings[S_numReadings];    // the readings from the analog input
int  S_readIndex = 0;              // the index of the current reading
long S_total = 0;                  // the running total
long S_average = 0;                // the average

CapacitiveSensor   CapButton1 = CapacitiveSensor(6,5);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   CapButton2 = CapacitiveSensor(4,3);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil

void setup() {
  Serial.begin(9600);
  // initialize all the readings to 0:
  // initialize all the readings to 0:
  for (int C_thisReading = 0; C_thisReading < C_numReadings; C_thisReading++) {
    C_readings[C_thisReading] = 0;
  }
  for (int S_thisReading = 0; S_thisReading < S_numReadings; S_thisReading++) {
    S_readings[S_thisReading] = 0;
  }
}

void loop() {

  long start = millis();
  long total1 =  CapButton1.capacitiveSensor(30);
  long total2 =  CapButton2.capacitiveSensor(30);

  C_total = C_total - C_readings[C_readIndex];
  S_total = S_total - S_readings[S_readIndex];
  // 2total = 2total - 2readings[2readIndex];
  // read from the sensor:
  C_readings[C_readIndex] = total1;
  S_readings[S_readIndex] = total2;
  // 2readings[2readIndex] = total2
  // add the reading to the total:
  C_total = C_total + C_readings[C_readIndex];
  S_total = S_total + S_readings[S_readIndex];
  // 2total = 2total + 2readings[2readIndex];
  // advance to the next position in the array:
  C_readIndex = C_readIndex + 1;
  S_readIndex = S_readIndex + 1;
  // 2readIndex = 2readIndex + 1;
  // if we're at the end of the array...
  if (C_readIndex >= C_numReadings) {
    // ...wrap around to the beginning:
    C_readIndex = 0;
  }
  if (S_readIndex >= S_numReadings) {
    // ...wrap around to the beginning:
    S_readIndex = 0;
  }

  // calculate the average:
  C_average = C_total / C_numReadings;
  // calculate the average:
  S_average = S_total / S_numReadings;

  Serial.print("average 1:");
  Serial.print("\t");
  Serial.print(C_average);
  Serial.print("\t");
  Serial.print("real 1:");
  Serial.print("\t");
  Serial.print(total1);
  Serial.print("\t");
  Serial.print("average 2:");
  Serial.print("\t");
  Serial.print(S_average);
  Serial.print("\t");
  Serial.print("real 2:");
  Serial.print("\t");
  Serial.println(total2);

  if ((C_average > 100) || S_average > 100 ) {
    digitalWrite(22, HIGH);
  }
  else {
    digitalWrite(22, LOW);
  }
  delay(1);        // delay in between reads for stability
}
