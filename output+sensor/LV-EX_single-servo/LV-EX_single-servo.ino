#include <Servo.h>
Servo myservo;

const int pwPin = 7;
const int servoPin = 9;

//          LV-EZ INPUT
//variables needed to store values
int arraysize = 9;  //quantity of values to find the median (sample size). Needs to be an odd number
//declare an array to store the samples. not necessary to zero the array values here, it just makes the code clearer
int rangevalue[] = {  0, 0, 0, 0, 0, 0, 0, 0, 0};
long pulse, inches, cm;
int modE;

// SERVO OUTPUT
int servoInterval;

void setup() {
  Serial.begin(9600);
  delay(500);
  myservo.attach(servoPin);
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

  Serial.print("  inches: ");
  Serial.print(inches);
  Serial.print("  CM: ");
  Serial.println(cm);
  // END INPUT SENSOR ////////////////////

  // HAPTIC OUTPUT ///////////////////////
  servoInterval = map(cm, 5, 650, 100, 1000); // map distance input to interval between servo movements
  myservo.write(5);
  delay(servoInterval);
  myservo.write(175);
  delay(servoInterval - 10); // - 10 is componsating for above 10ms delay in sensor reading for looop

  Serial.print("Servo interval value: ");
  Serial.println(servoInterval);

  // END HAPTIC OUTPUT ///////////////////////
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
