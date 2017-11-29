int motorPin[] = {5,6,9,10,11};
const int distanceSensorPin = 3;

// LV-EZ INPUT
int arraysize = 9;
int rangevalue[] = {  0, 0, 0, 0, 0, 0, 0, 0, 0};
long pulse, inches, cm;
int modE;

void setup() {
    Serial.begin(9600);

    for (int x = 0; x < 5; x++) {
        pinMode(motorPin[x], OUTPUT);
    };

    pinMode(distanceSensorPin, INPUT);
}

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



    for (int x = 0; x < 5; x ++) {
        analogWrite(motorPin[x], 153);
        Serial.print("Pulse sent to motor: ");
        Serial.println(x);
        delay(2000);
        analogWrite(motorPin[x], 0);
        delay(500);
    };
    delay(3000);
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
