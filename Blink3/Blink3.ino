int NUM = 0, pin = 2, a = 3, b = 4, c = 5, d = 6, e = 7, f = 8, g = 9;
void setup() {
  Serial.begin(9600);
  pinMode(pin, INPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

}

// the loop function runs over and over again forever
void loop() {
  if (digitalRead(pin) == HIGH) {
    while (digitalRead(pin) == HIGH) {}
    delay(250);
    if (NUM == 0) {
      NUM = 1;
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
    }
    else {
      NUM = 0;
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
    }
  }
}
