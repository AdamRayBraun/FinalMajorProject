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

// Processing communication
bool PROCESSING_DATA_VIS = false;
char processing_command;

void setup() {
    Serial.begin(9600);

    if (PROCESSING_DATA_VIS == true) {
        establishContact();
    }

    for (int x = 0; x < 5; x++) {
        pinMode(MotorData[x].pin, OUTPUT);
    };

}

void loop() {

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
            Serial.print(cm);
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
