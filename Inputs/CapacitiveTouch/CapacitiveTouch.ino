#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   CT1 = CapacitiveSensor(22,24);
CapacitiveSensor   CT2 = CapacitiveSensor(26,28);
CapacitiveSensor   CT3 = CapacitiveSensor(30,32);
CapacitiveSensor   CT4 = CapacitiveSensor(34,36);

long total1 =  0;
long total2 =  0;
long total3 =  0;
long total4 =  0;

void setup()
{
   Serial.begin(9600);
   pinMode(4, OUTPUT);
   digitalWrite(4, LOW);
}

void loop()
{
    long start = millis();
    total1 =  CT1.capacitiveSensor(100);
    total3 =  CT3.capacitiveSensor(100);
    total2 =  CT2.capacitiveSensor(100);
    total4 =  CT4.capacitiveSensor(100);

    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.print(total1);                  // print sensor output 1
    Serial.print("\t");
    Serial.print(total2);                  // print sensor output 2
    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.print(total3);                  // print sensor output 1
    Serial.print("\t");
    Serial.println(total4);
    delay(10);                             // arbitrary delay to limit data to serial port
}
