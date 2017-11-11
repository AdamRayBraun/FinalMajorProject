#include <Wire.h>
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;

const int pwPin = 7;

// LV-EZ INPUT
int arraysize = 9;
int rangevalue[] = {  0, 0, 0, 0, 0, 0, 0, 0, 0};
long pulse, inches, cm;
int modE;

// motor OUTPUT
int distanceValue;

void setup() {
  Serial.begin(9600);
  drv.begin();
  drv.selectLibrary(1);
  drv.setMode(DRV2605_MODE_INTTRIG);
}

uint8_t effect = 64;

void loop() {

  // INPUT SENSOR ////////////////////
  pinMode(pwPin, INPUT);
  for (int i = 0; i < arraysize; i++) {
    pulse = pulseIn(pwPin, HIGH);
    rangevalue[i] = pulse;
    delay(10);
  }

  isort(rangevalue, arraysize);
  modE = mode(rangevalue, arraysize);
  // 147uS per inch
  inches = modE / 147;
  cm = inches * 2.54;

  Serial.print("Distance in CM: ");
  Serial.println(cm);
  // END INPUT SENSOR ////////////////////

  distanceValue = map(cm, 0, 650, 0, 100);

  if (distanceValue >= 0 && distanceValue < 10 ) {
      effect = 91;
  } else if (distanceValue >= 10 && distanceValue < 20 ) {
      effect = 64;
  } else if (distanceValue >= 20 && distanceValue < 30 ) {
      effect = 65;
  } else if (distanceValue >= 30 && distanceValue < 40 ) {
      effect = 66;
  } else if (distanceValue >= 40 && distanceValue < 60 ) {
      effect = 67;
  } else if (distanceValue >= 60 && distanceValue < 80 ) {
      effect = 68;
  } else if (distanceValue >= 80 && distanceValue <= 100 ) {
      effect = 69;
  }

  //  HAPTIC OUTPUT //////////////////////
  drv.setWaveform(0, effect);  // play effect
  drv.setWaveform(1, 0);       // end waveform
  drv.go();
  delay(300);
  // END HAPTIC OUTPUT ///////////////////
}



//Function to print the arrays.
void printArray(int *a, int n) {
  for (int i = 0; i < n; i++) {
    Serial.print(a[i], DEC);
    Serial.print(' ');
  }
  Serial.println();
}

// sort function (Author: Bill Gentles, Nov. 12, 2010)
void isort(int *a, int n) {
  //  *a is an array pointer function

  for (int i = 1; i < n; ++i) {
    int j = a[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < a[k]); k--) {
      a[k + 1] = a[k];
    }

    a[k + 1] = j;
  }
}

//Mode function, returning the mode or median.
int mode(int *x, int n) {

  int i = 0;
  int count = 0;
  int maxCount = 0;
  int mode = 0;
  int bimodal;
  int prevCount = 0;

  while (i < (n - 1)) {
    prevCount = count;
    count = 0;

    while (x[i] == x[i + 1]) {
      count++;
      i++;
    }

    if (count > prevCount & count > maxCount) {
      mode = x[i];
      maxCount = count;
      bimodal = 0;
    }

    if (count == 0) {
      i++;
    }

    if (count == maxCount) { //If the dataset has 2 or more modes.
      bimodal = 1;
    }

    if (mode == 0 || bimodal == 1) { //Return the median if there is no mode.
      mode = x[(n / 2)];
    }

    return mode;
  }
}
