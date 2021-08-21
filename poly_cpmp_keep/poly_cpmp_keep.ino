
#include <DS3231.h>
#include <Wire.h>
DS3231  clock;
bool h12Flag;
bool pmFlag;
int ID[7];
int NUM, tim = 10;
int digitPins[7] = {9, 10, 11, 12, 13, A0, A1}; //Digits: 1,2,3,4 <--put one resistor (ex: 220 Ohms, or 330 Ohms, etc, on each digit pin)
int segmentPins[7] = {2, 3, 4, 5, 6, 7, 8}; //Segments: A,B,C,D,E,F,G,Period
unsigned long bth = 0, btm = 0;
int hrs_plus = A6, min_plus = A7;
int hrs_var = 0, min_var = 0;
String hr, mi, temp;

byte Hour;
byte Minute;

void GetDateStuff(byte& Hour, byte& Minute) {
  // Call this if you notice something coming in on
  // the serial port. The stuff coming in should be in
  // the order YYMMDDwHHMMSS, with an 'x' at the end.
  boolean GotString = false;
  char InChar;
  byte Temp1, Temp2;
  char InString[2];
  if (digitalRead(hrs_plus) == HIGH) {
    hr = String(hr.toInt() + 1);
    if (hr.toInt() > 23) hr = String(0);
  }
  if (digitalRead(min_plus) == HIGH) {
    mi = String(mi.toInt() + 1);
    if (mi.toInt() > 59) mi = String(0);
  }
  if (hr.toInt() < 10) {
    hr = "0" + hr;
  }
  if (mi.toInt() < 10) {
    mi = "0" + mi;
  }
  InString[0] = hr[0];
  InString[1] = hr[1];
  Temp1 = (byte)InString[0] - 48;
  Temp2 = (byte)InString[1] - 48;
  Hour = Temp1 * 10 + Temp2;

  InString[0] = mi[0];
  InString[1] = mi[1];
  Temp1 = (byte)InString[0] - 48;
  Temp2 = (byte)InString[1] - 48;
  Minute = Temp1 * 10 + Temp2;
}

void setup() {
  Wire.begin();
  Serial.begin(9600);

  pinMode(digitPins[0], OUTPUT);
  pinMode(digitPins[1], OUTPUT);
  pinMode(digitPins[2], OUTPUT);
  pinMode(digitPins[3], OUTPUT);
  pinMode(digitPins[4], OUTPUT);
  pinMode(digitPins[5], OUTPUT);
  pinMode(digitPins[6], OUTPUT);
  pinMode(segmentPins[0], OUTPUT);
  pinMode(segmentPins[1], OUTPUT);
  pinMode(segmentPins[2], OUTPUT);
  pinMode(segmentPins[3], OUTPUT);
  pinMode(segmentPins[4], OUTPUT);
  pinMode(segmentPins[5], OUTPUT);
  pinMode(segmentPins[6], OUTPUT);
  pinMode(hrs_plus, INPUT);
  pinMode(min_plus, INPUT);

  clock.setClockMode(false);

  for (int i = 0; i < 7; i++) {
    digitalWrite(digitPins[i], LOW);
  }
}

void loop() {
  getAndDisplay();
  if (digitalRead(hrs_plus) == HIGH && millis() < bth) {
    bth = millis() + 500;
    GetDateStuff(Hour, Minute);
    clock.setHour(Hour);
  }
  if (digitalRead(min_plus) == HIGH && millis() < btm) {
    btm = millis() + 500;
    GetDateStuff(Hour, Minute);
    clock.setMinute(Minute);
  }
}


void getAndDisplay() {
  hr = String (clock.getHour(h12Flag, pmFlag), DEC);
  mi = String (clock.getMinute(), DEC);
  temp = String (clock.getTemperature(), 2);
  if (hr == "0") {
    hr = "00";
  }
  else if (hr.toInt() < 10) {
    hr = "0" + hr;
  }
  if (mi == "0") {
    mi = "00";
  }
  else if (mi.toInt() < 10) {
    mi = "0" + mi;
  }
  if (temp == "0") {
    temp = "000";
  }
  else if (temp.toInt() < 10) {
    temp = "00" + temp;
  }
  else if (temp.toInt() < 100) {
    temp = "0" + temp;
  }
  String SDIGIT = hr + mi + temp;
  Serial.println(SDIGIT);
  //  String SDIGIT = String(DIGIT);
  String D1 = SDIGIT.substring (0, 1);
  ID[0] = D1.toInt();
  //_____________________________________________________________________________
  String D2 = SDIGIT.substring (1, 2);
  ID[1] = D2.toInt();
  //_____________________________________________________________________________
  String D3 = SDIGIT.substring (2, 3);
  ID[2] = D3.toInt();
  //_____________________________________________________________________________
  String D4 = SDIGIT.substring (3, 4);
  ID[3] = D4.toInt();
  //_____________________________________________________________________________
  String D5 = SDIGIT.substring (4, 5);
  ID[4] = D5.toInt();
  //_____________________________________________________________________________
  String D6 = SDIGIT.substring (5, 6);
  ID[5] = D6.toInt();
  //_____________________________________________________________________________
  String D7 = SDIGIT.substring (6, 7);
  ID[6] = D7.toInt();

  for (int i = 0; i < 7; i++) {
    if (i == 0) {
      digitalWrite(digitPins[6], LOW);
    }
    else {
      digitalWrite(digitPins[(i - 1)], LOW);
    }
    digitalWrite(digitPins[i], HIGH);
    NUM = ID[i];
    NUM7();
    delay(tim);
  }
}


void NUM7() {
  switch (NUM) {
    case 0:
      digitalWrite(segmentPins[0], HIGH); //A
      digitalWrite(segmentPins[1], HIGH); //B
      digitalWrite(segmentPins[2], HIGH); //C
      digitalWrite(segmentPins[3], HIGH); //D
      digitalWrite(segmentPins[4], HIGH); //E
      digitalWrite(segmentPins[5], HIGH); //F
      digitalWrite(segmentPins[6], LOW); //G
      break;
    case 1:
      digitalWrite(segmentPins[0], LOW); //A
      digitalWrite(segmentPins[1], HIGH); //B
      digitalWrite(segmentPins[2], HIGH); //C
      digitalWrite(segmentPins[3], LOW); //D
      digitalWrite(segmentPins[4], LOW); //E
      digitalWrite(segmentPins[5], LOW); //F
      digitalWrite(segmentPins[6], LOW); //G
      break;
    case 2:
      digitalWrite(segmentPins[0], HIGH); //A
      digitalWrite(segmentPins[1], HIGH); //B
      digitalWrite(segmentPins[2], LOW); //C
      digitalWrite(segmentPins[3], HIGH); //D
      digitalWrite(segmentPins[4], HIGH); //E
      digitalWrite(segmentPins[5], LOW); //F
      digitalWrite(segmentPins[6], HIGH); //G
      break;
    case 3:
      digitalWrite(segmentPins[0], HIGH); //A
      digitalWrite(segmentPins[1], HIGH); //B
      digitalWrite(segmentPins[2], HIGH); //C
      digitalWrite(segmentPins[3], HIGH); //D
      digitalWrite(segmentPins[4], LOW); //E
      digitalWrite(segmentPins[5], LOW); //F
      digitalWrite(segmentPins[6], HIGH); //G
      break;
    case 4:
      digitalWrite(segmentPins[0], LOW); //A
      digitalWrite(segmentPins[1], HIGH); //B
      digitalWrite(segmentPins[2], HIGH); //C
      digitalWrite(segmentPins[3], LOW); //D
      digitalWrite(segmentPins[4], LOW); //E
      digitalWrite(segmentPins[5], HIGH); //F
      digitalWrite(segmentPins[6], HIGH); //G
      break;
    case 5:
      digitalWrite(segmentPins[0], HIGH); //A
      digitalWrite(segmentPins[1], LOW); //B
      digitalWrite(segmentPins[2], HIGH); //C
      digitalWrite(segmentPins[3], HIGH); //D
      digitalWrite(segmentPins[4], LOW); //E
      digitalWrite(segmentPins[5], HIGH); //F
      digitalWrite(segmentPins[6], HIGH); //G
      break;
    case 6:
      digitalWrite(segmentPins[0], HIGH); //A
      digitalWrite(segmentPins[1], LOW); //B
      digitalWrite(segmentPins[2], HIGH); //C
      digitalWrite(segmentPins[3], HIGH); //D
      digitalWrite(segmentPins[4], HIGH); //E
      digitalWrite(segmentPins[5], HIGH); //F
      digitalWrite(segmentPins[6], HIGH); //G
      break;
    case 7:
      digitalWrite(segmentPins[0], HIGH); //A
      digitalWrite(segmentPins[1], HIGH); //B
      digitalWrite(segmentPins[2], HIGH); //C
      digitalWrite(segmentPins[3], LOW); //D
      digitalWrite(segmentPins[4], LOW); //E
      digitalWrite(segmentPins[5], LOW); //F
      digitalWrite(segmentPins[6], LOW); //G
      break;
    case 8:
      digitalWrite(segmentPins[0], HIGH); //A
      digitalWrite(segmentPins[1], HIGH); //B
      digitalWrite(segmentPins[2], HIGH); //C
      digitalWrite(segmentPins[3], HIGH); //D
      digitalWrite(segmentPins[4], HIGH); //E
      digitalWrite(segmentPins[5], HIGH); //F
      digitalWrite(segmentPins[6], HIGH); //G
      break;
    case 9:
      digitalWrite(segmentPins[0], HIGH); //A
      digitalWrite(segmentPins[1], HIGH); //B
      digitalWrite(segmentPins[2], HIGH); //C
      digitalWrite(segmentPins[3], LOW); //D
      digitalWrite(segmentPins[4], LOW); //E
      digitalWrite(segmentPins[5], HIGH); //F
      digitalWrite(segmentPins[6], HIGH); //G
      break;
  }
}
