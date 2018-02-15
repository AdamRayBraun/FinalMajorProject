int motorPin[] = {5,6,9,10};

void setup() {
    Serial.begin(9600);
    for (int x = 0; x < 4; x++) {
        pinMode(motorPin[x], OUTPUT);
    };
}

void loop() {

    for (int x = 0; x < 4; x ++) {
        analogWrite(motorPin[x], 153);
        Serial.print("Pulse sent to motor: ");
        Serial.println(x);
        delay(2000);
        analogWrite(motorPin[x], 0);
        delay(500);
    };
    delay(3000);
}
