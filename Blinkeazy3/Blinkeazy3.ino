int a = 2, b = 3, c = 4;
int tade = 0;
void setup() {
  Serial.begin(9600);
  pinMode(a, INPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  //BUTTON
  if (digitalRead(a) == HIGH) {
    while (digitalRead(a) == HIGH) {}
    delay(250);
    //WHAT BUTTON WILL DO
    tade++;
    if (tade == 4) {
      tade = 0;
    }
  }
  //BUTTON END
  switch (tade) {
    case 0:
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      break;
    case 1:
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      break;
    case 2:
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      break;
    case 3:
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      break;
  }
}
