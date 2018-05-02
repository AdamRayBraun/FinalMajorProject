int motorPin = 13;

void setup() {
  Serial.begin(9600);

  pinMode(motorPin, OUTPUT);
}

void loop() {

  analogWrite(motorPin, 153);
  Serial.println("ON");
  delay(1000);

  analogWrite(motorPin, 0);
  Serial.println("off");
  delay(3000);
}
