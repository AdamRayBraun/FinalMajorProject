struct motor {
    int pin;
    int Lower_placement;
    int Upper_placement;
    int motorStrength;
};

// Value 0 = GPIO pin
// value 1 = arbitrary lower distance each motor gives feedback for
// value 2 = arbitrary upper distance each motor gives feedback for
// Value 3 = empty at first then continuosly populated with strength of each motor
struct motor MotorData[] = {{ 5, 0, 75, 0 },
                            { 6, 25, 140, 0 },
                            { 9, 90, 280, 0 },
                            { 10, 230, 450, 0 },
                            { 11, 400, 650, 0 }
                        };

const int distanceSensorPin = 3;

// LV-EZ INPUT
int arraysize = 9;
int rangevalue[] = {  0, 0, 0, 0, 0, 0, 0, 0, 0};
long pulse, inches, cm;
int modE;

// Processing communication
bool PROCESSING_DATA_VIS = true;
char processing_command;

void setup() {
    Serial.begin(9600);

    if (PROCESSING_DATA_VIS == true) {
        establishContact();
    }

    for (int x = 0; x < 5; x++) {
        pinMode(MotorData[x].pin, OUTPUT);
    };

    pinMode(distanceSensorPin, INPUT);
}

void loop() {

        // INPUT SENSOR ////////////////////
    pinMode(distanceSensorPin, INPUT);
    for (int i = 0; i < arraysize; i++) {
      pulse = pulseIn(distanceSensorPin, HIGH);
      rangevalue[i] = pulse;
      delay(10);
    }
    isort(rangevalue, arraysize);
    modE = mode(rangevalue, arraysize);
    // 147uS per inch
    inches = modE / 147;
    cm = inches * 2.54;
    // Serial.print("Dist CM: ");
    // Serial.print(cm);
        // END INPUT SENSOR ////////////////////

    // for each motor TODO change to length of motors in struct
    for (int x = 0; x < 5; x ++) {

        // if distance is within bounds of the motor
        if (cm < MotorData[x].Upper_placement && cm > MotorData[x].Lower_placement) {

            // map (distance from position to each motor) to (strength of each motor)
            MotorData[x].motorStrength = map(cm, MotorData[x].Lower_placement, MotorData[x].Upper_placement, 0, 153);
        }
        else {
            MotorData[x].motorStrength = 0;
        }

        // Send each motors it's new strentgh based on distance
        analogWrite(MotorData[x].pin, MotorData[x].motorStrength);

        // Serial.print(MotorData[x].motorStrength);
        // Serial.print(" ");
    };

    if (PROCESSING_DATA_VIS == true) {
        // if data is available to read
        if (Serial.available() > 0) {
            processing_command = Serial.read();

            if (processing_command == '1') {
                ; // do something
            }
            delay(100);
        }
        // else send motor data
        else {
            Serial.print("CM: ");
            Serial.print(cm);
            Serial.print(" Motor Strength: ");
            for (int x = 0; x < 5; x++) {
                Serial.print(MotorData[x].motorStrength);
                if (x != 4) {
                    Serial.print(",");
                }
            }
            Serial.println(" ");

            delay(50);
        }
    }
}


// establish data contact with processing_command
void establishContact() {
    while (Serial.available() <= 0) {
        Serial.println("A");
        delay(300);
    }
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

//Mode function, returning the mode
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
