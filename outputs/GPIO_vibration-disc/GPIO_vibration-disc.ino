const int motorPin = 3;

void setup() {
    Serial.begin(9600);
    pinMode(motorPin, OUTPUT);
}

void loop() {

    for (int x = 0; x < 154; x ++) {
        analogWrite(motorPin, 153);
        Serial.print("Pulse val: ");
        Serial.println(x);
        delay(10);

    analogWrite(motorPin, 0);
    delay(3000);
}
