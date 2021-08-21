
#include <LiquidCrystal.h>
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int testPin = 4, hold = 3, trigPin = 2;
//5 is the input to the circuit (connects to 150ohm resistor), 11 is the comparator/op-amp output.
double F_0 = 0.0, C_0 = 1.0E-6, L_0 = 1.0E-6, F_N, C_N, L_N, F_D;

void setup() {
  lcd.begin(16, 2);
  lcd.print("eazy");
  pinMode(5, INPUT);
  pinMode(hold, INPUT_PULLUP);
  pinMode(testPin, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);
  for (int i = 0; i < 5; i++) {
    test_L_0();
    delay(5);
  }
}
void loop() {
  if (digitalRead(testPin) == LOW) {
    while (digitalRead(testPin) == LOW) {}
    for (int i = 0; i < 3; i++) {
      test_L_0();
      delay(5);
    }
      delay(2000);
  }

  digitalWrite(trigPin, HIGH);
  delay(5);//give some time to charge inductor.
  digitalWrite(trigPin, LOW);
  delayMicroseconds(100); //make sure resonation is measured
  F_N = pulseIn(5, HIGH, 5000); //returns 0 if timeout
  if (F_N > 0.1) {
    F_N = 1.E6 / (F_N * 2);
    F_D = F_N;
    F_Display();
    
    if (F_N > F_0) {
      test_L_N();
    }
    else if (F_N < F_0) {
      test_C_N();
    }
  }

  while (digitalRead(hold) == LOW) {}
  delay(10);
}



void F_Display() {
  lcd.clear();
  lcd.home();
  lcd.print("F = ");

  if (F_D > 999999.9999) {
    F_D /= 1E6;
    lcd.print(F_D);
    lcd.setCursor(12, 0);
    lcd.print(" MHz");
  }
  else if (F_D > 999.9999999) {
    F_D /= 1E3;
    lcd.print(F_D);
    lcd.setCursor(12, 0);
    lcd.print(" kHz");
  }
  else if (F_D > 9.999999999E-1) {
    F_D = F_D;
    lcd.print(F_D);
    lcd.setCursor(12, 0);
    lcd.print(" Hz ");
  }
  else if (F_D > 9.999999999E-4) {
    F_D *= 1E3;
    lcd.print(F_D);
    lcd.setCursor(12, 0);
    lcd.print(" mHz");
  }
  else if (F_D > 9.999999999E-7) {
    F_D *= 1E6;
    lcd.print(F_D);
    lcd.setCursor(12, 0);
    lcd.print(" uHz");
  }
  else if (F_D > 9.999999999E-10) {
    F_D *= 1E9;
    lcd.print(F_D);
    lcd.setCursor(12, 0);
    lcd.print(" nHz");
  }
  else if (F_D > 9.999999999E-13) {
    F_D *= 1E12;
    lcd.print(F_D);
    lcd.setCursor(12, 0);
    lcd.print(" pHz");
  }
  else {
    lcd.print(F_D);
    lcd.setCursor(12, 0);
    lcd.print(" Hz ");
  }
}

void test_L_0() {
  digitalWrite(trigPin, HIGH);
  delay(5);//give some time to charge inductor.
  digitalWrite(trigPin, LOW);
  delayMicroseconds(100); //make sure resonation is measured
  F_0 = pulseIn(5, HIGH, 5000); //returns 0 if timeout
  if (F_0 > 0.1) {
    F_0 = 1.E6 / (F_0 * 2);
    F_D = F_0;
    F_Display();
    L_0 = 1.0 / (C_0 * F_0 * F_0 * 4.0 * 3.14159 * 3.14159);
    lcd.setCursor(0, 1);
    lcd.print("L = ");
    if (L_0 > 999999.9999) {
      L_0 /= 1E6;
      lcd.print(L_0);
      lcd.setCursor(13, 1);
      lcd.print(" MH");
    }
    else if (L_0 > 999.9999999) {
      L_0 /= 1E3;
      lcd.print(L_0);
      lcd.setCursor(13, 1);
      lcd.print(" kH");
    }
    else if (L_0 > 9.999999999E-1) {
      L_0 = L_0;
      lcd.print(L_0);
      lcd.setCursor(13, 1);
      lcd.print("  H");
    }
    else if (L_0 > 9.999999999E-4) {
      L_0 *= 1E3;
      lcd.print(L_0);
      lcd.setCursor(13, 1);
      lcd.print(" mH");
    }
    else if (L_0 > 9.999999999E-7) {
      L_0 *= 1E6;
      lcd.print(L_0);
      lcd.setCursor(13, 1);
      lcd.print(" uH");
    }
    else if (L_0 > 9.999999999E-10) {
      L_0 *= 1E9;
      lcd.print(L_0);
      lcd.print(" nH");
    }
    else if (L_0 > 9.999999999E-13) {
      L_0 *= 1E12;
      lcd.print(L_0);
      lcd.setCursor(13, 1);
      lcd.print(" pH");
    }
    else {
      lcd.print(L_0);
      lcd.setCursor(13, 1);
      lcd.print("  H");
    }
  }
}

void test_L_N() {
  L_N = L_0 / ((L_0 * C_0 * F_0 * F_0 * 4.0 * 3.14159 * 3.14159) - 1);
  lcd.setCursor(0, 1);
  lcd.print("L = ");
  if (L_N > 999999.9999) {
    L_N /= 1E6;
    lcd.print(L_N);
    lcd.setCursor(13, 1);
    lcd.print(" MH");
  }
  else if (L_N > 999.9999999) {
    L_N /= 1E3;
    lcd.print(L_N);
    lcd.setCursor(13, 1);
    lcd.print(" kH");
  }
  else if (L_N > 9.999999999E-1) {
    L_N = L_N;
    lcd.print(L_N);
    lcd.setCursor(13, 1);
    lcd.print(" H");
  }
  else if (L_N > 9.999999999E-4) {
    L_N *= 1E3;
    lcd.print(L_N);
    lcd.setCursor(13, 1);
    lcd.print(" mH");
  }
  else if (L_N > 9.999999999E-7) {
    L_N *= 1E6;
    lcd.print(L_N);
    lcd.setCursor(13, 1);
    lcd.print(" uH");
  }
  else if (L_N > 9.999999999E-10) {
    L_N *= 1E9;
    lcd.print(L_N);
    lcd.setCursor(13, 1);
    lcd.print(" nH");
  }
  else if (L_N > 9.999999999E-13) {
    L_N *= 1E12;
    lcd.print(L_N);
    lcd.setCursor(13, 1);
    lcd.print(" pH");
  }
  else {
    lcd.print(L_N);
    lcd.setCursor(13, 1);
    lcd.print("  H");
  }
}

void test_C_N() {
  C_N = (1.0 / (L_0 * F_0 * F_0 * 4.0 * 3.14159 * 3.14159)) - C_0;

  lcd.setCursor(0, 1);
  lcd.print("C = ");
  if (C_N > 999999.9999) {
    C_N /= 1E6;
    lcd.print(C_N);
    lcd.setCursor(13, 1);
    lcd.print(" MF");
  }
  else if (C_N > 999.9999999) {
    C_N /= 1E3;
    lcd.print(C_N);
    lcd.setCursor(13, 1);
    lcd.print(" kF");
  }
  else if (C_N > 9.999999999E-1) {
    C_N = C_N;
    lcd.print(C_N);
    lcd.setCursor(13, 1);
    lcd.print(" F ");
  }
  else if (C_N > 9.999999999E-4) {
    C_N *= 1E3;
    lcd.print(C_N);
    lcd.setCursor(13, 1);
    lcd.print(" mF");
  }
  else if (C_N > 9.999999999E-7) {
    C_N *= 1E6;
    lcd.print(C_N);
    lcd.setCursor(13, 1);
    lcd.print(" uF");
  }
  else if (C_N > 9.999999999E-10) {
    C_N *= 1E9;
    lcd.print(C_N);
    lcd.setCursor(13, 1);
    lcd.print(" nF");
  }
  else if (C_N > 9.999999999E-13) {
    C_N *= 1E12;
    lcd.print(C_N);
    lcd.setCursor(13, 1);
    lcd.print(" pF");
  }
  else {
    lcd.print(C_N);
    lcd.setCursor(13, 1);
    lcd.print("  F");
  }
}
