int motorPin[] = {10,11,12,13};

int SB_SUB_RST = 44;
int SB_SUB[] = {42,40,38,36,34,32,30,28,26,24,22};

int SB_BONE_RST = 27;
int SB_BONE[] = {29,31,33,35,37,39,41,43,45,47,49};

void setup() {

    for (int x = 0; x < 4; x++){
      pinMode(motorPin[x], OUTPUT);
    }
    for (int x = 0; x < 10; x++){
      pinMode(SB_BONE[x], OUTPUT);
    }
    for (int x = 0; x < 10; x++){
      pinMode(SB_SUB[x], OUTPUT);
    }
    pinMode(SB_BONE_RST, OUTPUT);
    pinMode(SB_SUB_RST, OUTPUT);
}

void loop() {

  // All motors on
  for (int x = 0; x < 5; x++){
    analogWrite(motorPin[x], 153);
  }

  // Trigger T01 on both soundboards
  digitalWrite(SB_SUB_RST, HIGH);
  digitalWrite(SB_SUB[1], LOW);
  digitalWrite(SB_BONE_RST, HIGH);
  digitalWrite(SB_BONE[1], LOW);

  delay(10000);

  for (int x = 0; x < 5; x++){
    analogWrite(motorPin[x], 0);
  }

  // Reset both soundboards
  digitalWrite(SB_SUB_RST, LOW);
  digitalWrite(SB_SUB[1], HIGH);
  digitalWrite(SB_BONE_RST, LOW);
  digitalWrite(SB_BONE[1], HIGH);

  delay(5000);
}
