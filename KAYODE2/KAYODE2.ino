unsigned long former_time = 0;
int a1 = 0, a2 = 3, b1 = 4, b2 = 4, c1 = 9, c2 = 0;
int a = 6, b = 7, c = 5, d = 4, e = 3, f = 8, g = 2;
int AA1 = A3, AA2 = A1, BB1 = A4, BB2 = A2, CC1 = A5, CC2 = A0;
int del = 2;
int off_p = 1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(AA1, OUTPUT);
  pinMode(BB1, OUTPUT);
  pinMode(AA2, OUTPUT);
  pinMode(BB2, OUTPUT);
  pinMode(CC1, OUTPUT);
  pinMode(CC2, OUTPUT);
  digitalWrite(CC2, HIGH);
  digitalWrite(CC1, HIGH);
  digitalWrite(BB2, HIGH);
  digitalWrite(BB1, HIGH);
  digitalWrite(AA2, HIGH);
  digitalWrite(AA1, HIGH);
}

void loop() {
    // put your main code here, to run repeatedly:
    if (millis() >= former_time + 1000) {
      former_time = millis();
      a1++;
      if (a1 > 9) {
        a1 = 0;
        a2++;
      }
      if (a2 >= 6) {
        a2 = 0;
        b1++;
      }
  
      if (b1 > 9) {
        b1 = 0;
        b2++;
      }
      if (b2 >= 6) {
        b2 = 0;
        c1++;
      }
  
      if (c1 > 9) {
        c1 = 0;
        c2++;
      }
      if (c2 == 1 && c1 == 2) {
        c1 = 0;
        c2 = 0;
      }
      Serial.print(c2);
      Serial.print(c1);
      Serial.print(" : ");
      Serial.print(b2);
      Serial.print(b1);
      Serial.print(" : ");
      Serial.print(a2);
      Serial.println(a1);
    }
  
  digits(a1);
  digitalWrite(AA1, LOW);
  digitalWrite(AA2, HIGH);
  digitalWrite(BB1, HIGH);
  digitalWrite(BB2, HIGH);
  digitalWrite(CC1, HIGH);
  digitalWrite(CC2, HIGH);
  delay(del);
  digitalWrite(AA1, HIGH);
  digitalWrite(AA2, HIGH);
  digitalWrite(BB1, HIGH);
  digitalWrite(BB2, HIGH);
  digitalWrite(CC1, HIGH);
  digitalWrite(CC2, HIGH);
  delay(off_p);
  digits(a2);
  digitalWrite(AA1, HIGH);
  digitalWrite(AA2, LOW);
  digitalWrite(BB1, HIGH);
  digitalWrite(BB2, HIGH);
  digitalWrite(CC1, HIGH);
  digitalWrite(CC2, HIGH);
  delay(del);
  digitalWrite(AA1, HIGH);
  digitalWrite(AA2, HIGH);
  digitalWrite(BB1, HIGH);
  digitalWrite(BB2, HIGH);
  digitalWrite(CC1, HIGH);
  digitalWrite(CC2, HIGH);
  delay(off_p);

  digits(b1);
  digitalWrite(AA1, HIGH);
  digitalWrite(AA2, HIGH);
  digitalWrite(BB1, LOW);
  digitalWrite(BB2, HIGH);
  digitalWrite(CC1, HIGH);
  digitalWrite(CC2, HIGH);
  delay(del);
  digitalWrite(AA1, HIGH);
  digitalWrite(AA2, HIGH);
  digitalWrite(BB1, HIGH);
  digitalWrite(BB2, HIGH);
  digitalWrite(CC1, HIGH);
  digitalWrite(CC2, HIGH);
  delay(off_p);
  digits(b2);
  digitalWrite(AA1, HIGH);
  digitalWrite(AA2, HIGH);
  digitalWrite(BB1, HIGH);
  digitalWrite(BB2, LOW);
  digitalWrite(CC1, HIGH);
  digitalWrite(CC2, HIGH);
  delay(del);
  digitalWrite(AA1, HIGH);
  digitalWrite(AA2, HIGH);
  digitalWrite(BB1, HIGH);
  digitalWrite(BB2, HIGH);
  digitalWrite(CC1, HIGH);
  digitalWrite(CC2, HIGH);
  delay(off_p);

  digits(c1);
  digitalWrite(AA1, HIGH);
  digitalWrite(AA2, HIGH);
  digitalWrite(BB1, HIGH);
  digitalWrite(BB2, HIGH);
  digitalWrite(CC1, LOW);
  digitalWrite(CC2, HIGH);
  delay(del);
  digitalWrite(AA1, HIGH);
  digitalWrite(AA2, HIGH);
  digitalWrite(BB1, HIGH);
  digitalWrite(BB2, HIGH);
  digitalWrite(CC1, HIGH);
  digitalWrite(CC2, HIGH);
  delay(off_p);
  digits(c2);
  digitalWrite(AA1, HIGH);
  digitalWrite(AA2, HIGH);
  digitalWrite(BB1, HIGH);
  digitalWrite(BB2, HIGH);
  digitalWrite(CC1, HIGH);
  digitalWrite(CC2, LOW);
  delay(del);
  digitalWrite(AA1, HIGH);
  digitalWrite(AA2, HIGH);
  digitalWrite(BB1, HIGH);
  digitalWrite(BB2, HIGH);
  digitalWrite(CC1, HIGH);
  digitalWrite(CC2, HIGH);
  delay(off_p);
}



void digits(int seg) {
  switch (seg) {
    case 0:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      break;
    case 1:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 2:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 3:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 4:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 5:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 6:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 7:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 8:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 9:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;

      
    case 10:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 11:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 12:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 13:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 14:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;
    case 15:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      break;
    case 16:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
  }
}
