int motorPin[] = {9,10,11,12,13};

void setup() {
    // Serial.begin(9600);

    for (int x = 0; x < 5; x++){
      pinMode(motorPin[x], OUTPUT);
    }
}

void loop() {

  for (int x = 0; x < 5; x++){
    analogWrite(motorPin[x], 153);
  }
  delay(1000);

  for (int x = 0; x < 5; x++){
    analogWrite(motorPin[x], 0);
  }
  delay(3000);

}
