
int pinA = A0; //for an analog reading
int b1 = 2, b2 = 3, b3 = 4, b4 = 5, b5 = 6, b6 = 7, b7 = 8;
int sp = 10; //for analog output


void setup() {
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(b5, INPUT);
  pinMode(b6, INPUT);
  pinMode(b7, INPUT);
  pinMode(sp, OUTPUT);

}
void loop() {
  int tone1 = 261;
  int tone2 = 293;
  int tone3 = 329;
  int tone4 = 349;
  int tone5 = 391;
  int tone6 = 440;
  int tone7 = 493;

  while (digitalRead(b1) == HIGH) {
    tone(sp, tone1);
  }
  noTone(sp);

  while (digitalRead(b2) == HIGH) {
    tone(sp, tone2);
  }
  noTone(sp);

  while (digitalRead(b3) == HIGH) {
    tone(sp, tone3);
  }
  noTone(sp);

  while (digitalRead(b4) == HIGH) {
    tone(sp, tone4);
  }
  noTone(sp);

  while (digitalRead(b5) == HIGH) {
    tone(sp, tone5);
  }
  noTone(sp);

  while (digitalRead(b6) == HIGH) {
    tone(sp, tone6);
  }
  noTone(sp);

  while (digitalRead(b7) == HIGH) {
    tone(sp, tone7);
  }
  noTone(sp);
}
