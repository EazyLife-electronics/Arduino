int a = 2, b = 3;
int tade = 0;
void setup() {
  Serial.begin(9600);
  pinMode(a, INPUT);
  pinMode(b, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  //BUTTON
  if (digitalRead(a) == HIGH) {
    while (digitalRead(a) == HIGH) {}
    delay(250);
    //WHAT BUTTON WILL DO
    if (tade == 0) {
      tade = 1;
    }
    else {
      tade = 0;
    }
  }
  //BUTTON END
  
  if (tade == 1) {
    digitalWrite(b, HIGH);
  }
  if (tade == 0) {
    digitalWrite(b, LOW);
  }

}
