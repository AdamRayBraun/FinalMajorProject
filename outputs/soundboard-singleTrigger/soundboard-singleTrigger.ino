int SB_SUB_1 = 40;
int SB_SUB_RST = 44;
int SB_BONE_1 = 31;
int SB_BONE_RST = 27;

void setup() {
  pinMode(SB_SUB_1, OUTPUT);
  pinMode(SB_SUB_RST, OUTPUT);
  pinMode(SB_BONE_1, OUTPUT);
  pinMode(SB_BONE_RST, OUTPUT);
}

void loop() {
  // Reset both soundboards
  digitalWrite(SB_SUB_RST, LOW);
  digitalWrite(SB_SUB_1, HIGH);
  digitalWrite(SB_BONE_RST, LOW);
  digitalWrite(SB_BONE_1, HIGH);

  delay(5000); //wait 5 secs

  // Trigger T01 on both soundboards
  digitalWrite(SB_SUB_RST, HIGH);
  digitalWrite(SB_SUB_1, LOW);
  digitalWrite(SB_BONE_RST, HIGH);
  digitalWrite(SB_BONE_1, LOW);

  delay(10000); //wait 10 secs
}
