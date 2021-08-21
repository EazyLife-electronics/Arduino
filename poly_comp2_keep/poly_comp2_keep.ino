
#include <DS3231.h>
#include <Wire.h>
DS3231  clock;
bool h12Flag;
bool pmFlag;
bool century = false;
int ID[6];
int NUM, tim = 10;
int digitPins[8] = {9, 10, 11, 12, 13, A0}; //Digits: 1,2,3,4 <--put one resistor (ex: 220 Ohms, or 330 Ohms, etc, on each digit pin)
int segmentPins[7] = {2, 3, 4, 5, 6, 7, 8}; //Segments: A,B,C,D,E,F,G,Period

  String dy,mo,yr;

unsigned long bty = 0, btm = 0, btd = 0;
int day_plus = A1, mon_plus = A2, yrs_plus = A3;
byte Year;
byte Month;
byte Date;


void GetDateStuff(byte& Year, byte& Month, byte& Day) {
  // Call this if you notice something coming in on
  // the serial port. The stuff coming in should be in
  // the order YYMMDDwHHMMSS, with an 'x' at the end.
  boolean GotString = false;
  char InChar;
  byte Temp1, Temp2;
  char InString[2];
  if (digitalRead(day_plus) == HIGH) {
    dy = String(dy.toInt() + 1);
    if (dy.toInt() > 23) dy = String(0);
  }
  if (digitalRead(mon_plus) == HIGH) {
    mo = String(mo.toInt() + 1);
    if (mo.toInt() > 12) mo = String(1);
  }
  if (digitalRead(yrs_plus) == HIGH) {
    yr = String(yr.toInt() + 1);
    if (yr.toInt() > 99) yr = String(0);
  }
  if (dy.toInt() < 10) {
    dy = "0" + dy;
  }
  if (mo.toInt() < 10) {
    mo = "0" + mo;
  }
  if (yr.toInt() < 10) {
    yr = "0" + yr;
  }
  InString[0] = dy[0];
  InString[1] = dy[1];
  Temp1 = (byte)InString[0] - 48;
  Temp2 = (byte)InString[1] - 48;
  Date = Temp1 * 10 + Temp2;

  InString[0] = mo[0];
  InString[1] = mo[1];
  Temp1 = (byte)InString[0] - 48;
  Temp2 = (byte)InString[1] - 48;
  Month = Temp1 * 10 + Temp2;
  
  InString[0] = yr[0];
  InString[1] = yr[1];
  Temp1 = (byte)InString[0] - 48;
  Temp2 = (byte)InString[1] - 48;
  Year = Temp1 * 10 + Temp2;
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
  pinMode(segmentPins[0], OUTPUT);
  pinMode(segmentPins[1], OUTPUT);
  pinMode(segmentPins[2], OUTPUT);
  pinMode(segmentPins[3], OUTPUT);
  pinMode(segmentPins[4], OUTPUT);
  pinMode(segmentPins[5], OUTPUT);
  pinMode(segmentPins[6], OUTPUT);
  pinMode(day_plus, INPUT);
  pinMode(mon_plus, INPUT);
  pinMode(yrs_plus, INPUT);

  for (int i = 0; i < 6; i++) {
    digitalWrite(digitPins[i], LOW);
  }
}

void loop() {
  getAndDisplay();
  if (digitalRead(day_plus) == HIGH && millis() < btd) {
    btd = millis() + 500;
    GetDateStuff(Year, Month, Date);
   clock.setDate(Date);
  }
  if (digitalRead(mon_plus) == HIGH && millis() < btm) {
    btm = millis() + 500;
    GetDateStuff(Year, Month, Date);
   clock.setMonth(Month);
  }
  if (digitalRead(yrs_plus) == HIGH && millis() < bty) {
    bty = millis() + 500;
    GetDateStuff(Year, Month, Date);
   clock.setYear(Year);
  }
}
void getAndDisplay() {
  dy = String (clock.getDate(), DEC);
  mo = String (clock.getMonth(century), DEC);
  yr = String (clock.getYear(), DEC);
  if (dy == "0") {
    dy = "00";
  }
  else if (dy.toInt() < 10) {
    dy = "0" + dy;
  }
  if (mo == "0") {
    mo = "00";
  }
  else if (mo.toInt() < 10) {
    mo = "0" + mo;
  }
  if (yr == "0") {
    yr = "00";
  }
  String SDIGIT = dy + mo + yr;
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

  for (int i = 0; i < 6; i++) {
    if (i == 0) {
      digitalWrite(digitPins[5], LOW);
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
