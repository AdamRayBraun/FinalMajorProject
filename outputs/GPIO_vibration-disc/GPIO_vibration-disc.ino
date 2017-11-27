const int motorPin = 3;

void setup()
{
pinMode(motorPin, OUTPUT);
}

void loop()
{
analogWrite(motorPin, 153);
delay(1000);
analogWrite(motorPin, 0);
delay(2000);
}
