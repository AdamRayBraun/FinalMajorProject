int SB_SUB[] = {42,40,38,36,34,32,30,28,26,24,22};
int SB_SUB_RST = 44;

int SB_BONE[] = {29,31,33,35,37,39,41,43,45,47,49};
int SB_BONE_RST = 27;

void setup() {
  pinMode(SB_SUB_RST, OUTPUT);
  pinMode(SB_BONE_RST, OUTPUT);

  for (int x=0; x<11; x++) {
    pinMode(SB_BONE[x], OUTPUT);
  }
}

void loop() {
  // Reset both soundboards
  digitalWrite(SB_SUB_RST, LOW);
  digitalWrite(SB_BONE_RST, LOW);

  for (int x=0; x<11; x++) {
    digitalWrite(SB_BONE[x], HIGH);
  }

  for (int x=0; x<11; x++) {
    digitalWrite(SB_SUB[x], HIGH);
  }

  delay(5000); //wait 5 secs

  // Trigger T01 on both soundboards
  digitalWrite(SB_SUB_RST, HIGH);
  digitalWrite(SB_SUB_RST, HIGH);

  for (int x=0; x<11; x++) {
    if (x == 1) {
      digitalWrite(SB_SUB[x], LOW);
    } else
    digitalWrite(SB_SUB[x], HIGH);
  }

  for (int x=0; x<11; x++) {
    if (x == 1) {
      digitalWrite(SB_BONE[x], LOW);
    } else {
      digitalWrite(SB_BONE[x], HIGH);
    }
  }

  delay(10000); //wait 10 secs
}
