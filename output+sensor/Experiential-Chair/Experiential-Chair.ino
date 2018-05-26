#include <CapacitiveSensor.h>
#include "motor.h"
#include "motor_array.h"
#include "CapButton.h"

/* TODO
-should recognise if serial connection is lost so it tries to establish
  connection again
*/

/* VARIABLES TO SOMETIMES CHANGE *///////////////////////////////////////////
  bool PROCESSING_DATA_VIS = false;
  bool VIBRATION_MOTORS = true;
  bool SOUND_OUTPUT = true;

  const int total_motors = 4;
  const int numberOfCapButtons = 4;
  const int Capacitive_threshold = 1400;

  // Soundboard pins starting with RST then T00 through to T10
  int SB_BONE[] = {29,31,33,35,37,39,41,43,45,47,49};
  int SB_BONE_RST = 27;

/* CONSTANT VARIABLES *//////////////////////////////////////////////////////

// Vibration motors
  static VibrationMotor *motors[total_motors];
  static MotorSequence  *motorSequence;

// capacitive touch buttons
  static CapButton *capacitiveButtons[numberOfCapButtons];
  long ButtonReadings[numberOfCapButtons];

  CapacitiveSensor   CT0 = CapacitiveSensor(22,24);
  CapacitiveSensor   CT1 = CapacitiveSensor(26,28);
  CapacitiveSensor   CT2 = CapacitiveSensor(30,32);
  CapacitiveSensor   CT3 = CapacitiveSensor(34,36);

// CapacitiveSensor CT0(22, 24);

// Processing communication
char processing_command;

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo

  // for communication with processing
  if (PROCESSING_DATA_VIS == true) {
      establishContact();
  }

  // vibration motor set up
  motorSequence = new MotorSequence();
  for (int x =0; x < total_motors; x++) {
    if (x == 0) {
      motors[x] = new VibrationMotor(motorSequence, 9+x, false);
    }
    else {
      motors[x] = new VibrationMotor(motorSequence, 9+x, false);
    }
  }


  // Capacitive touch buttons set up
  capacitiveButtons[0] = new CapButton(1400);
  capacitiveButtons[1] = new CapButton(1400);
  capacitiveButtons[2] = new CapButton(1400);
  capacitiveButtons[3] = new CapButton(1400);

  //Sound board set up
  // set all soundboard pins as outputs
  pinMode(SB_BONE_RST, OUTPUT);
  for (int x=0; x<11; x++) {
    pinMode(SB_BONE[x], OUTPUT);
    digitalWrite(SB_BONE[x], HIGH);
  }
  soundTriggerReset();
}

void loop() {
  // processing data visualisation
  if (PROCESSING_DATA_VIS == true) {
    procesingHandler();
    }
  else if (PROCESSING_DATA_VIS == false) {
  }

  // Motor sequecncing
  for (int x = 0; x < total_motors; x++) {
    motors[x]->Sequence();
  }

  // capacitive touch buttons
  ButtonReadings[0] = CT0.capacitiveSensor(100);
  ButtonReadings[1] = CT1.capacitiveSensor(100);
  ButtonReadings[2] = CT2.capacitiveSensor(100);
  ButtonReadings[3] = CT3.capacitiveSensor(100);

  for (int button = 0; button < numberOfCapButtons; button++) {
    capacitiveButtons[button]->Service(ButtonReadings[button]);
    if (capacitiveButtons[button]->buttonValue() == true) {
      scenarioTrigger(button);
    }
  }

  delay(10);        // arbitrary delay to limit data to serial port
}

void scenarioTrigger(int scenario) {
  if (VIBRATION_MOTORS == true) {
    for (int x = 0; x < total_motors; x++) {
      motors[x]->SequenceFire(scenario);
    }
  }

  if (SOUND_OUTPUT == true) {
    // turn off last pin and trigger passed sound
    digitalWrite(SB_BONE[scenario], LOW);
    delay(300);
    digitalWrite(SB_BONE[scenario], HIGH);

  }

  Serial.print("Scenario triggered: ");
  Serial.println(scenario);
}

void soundTriggerReset() {
  // turn off last pin and trigger RESET pin
  digitalWrite(SB_BONE_RST, LOW);
  delay(300);
  digitalWrite(SB_BONE_RST, HIGH);
}

void procesingHandler() {
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
        Serial.println("processing info");

        delay(50);
    }
}

// establish data contact with processing_command
void establishContact() {
    while (Serial.available() <= 0) {
        Serial.println("A");
        delay(300);
    }
}
