#include <DHT.h>
#define DHTPIN 11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int ID[3];
int NUM, tim = 10;
int digitPins[3] = {8, 9, 10}; //Digits: 1,2,3,4 <--put one resistor (ex: 220 Ohms, or 330 Ohms, etc, on each digit pin)
int segmentPins[7] = {1, 2, 3, 4, 5, 6, 7}; //Segments: A,B,C,D,E,F,G,Period
String dhtt;

String SDIGIT, D_STRING;

int segA = 0, segB = 0, segC = 0, segD = 0, segE = 0, segF = 0, segG = 0;

void setup() {
  dht.begin();
  for (int i = 0; i < 3; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(digitPins[i], LOW);
  }
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], LOW);
  }

}

void loop() {
  getAndDisplay();
}


void getAndDisplay() {
  dhtt = String (dht.readTemperature());
  if (dhtt == "0") {
    dhtt = "000";
  }
  else if (dhtt.toInt() < 10) {
    dhtt = "00" + dhtt;
  }
  else if (dhtt.toInt() < 100) {
    dhtt = "0" + dhtt;
  }
  SDIGIT = dhtt;

  for (int i = 0; i < 3; i++) {
    D_STRING = SDIGIT.substring (i, (i + 1));
    ID[i] = D_STRING.toInt();
  }

  for (int i = 0; i < 3; i++) {
    if (i == 0) {
      digitalWrite(digitPins[2], LOW);
    }
    else {
      digitalWrite(digitPins[(i - 1)], LOW);
    }
    digitalWrite(digitPins[i], HIGH);
    NUM = ID[i];
    NUM7();
    switch_7seg();
    delay(tim);
  }
}


void NUM7() {
  switch (NUM) {
    case 0:
      if (segA == 0)segA = 1;
      if (segB == 0)segB = 1;
      if (segC == 0)segC = 1;
      if (segD == 0)segD = 1;
      if (segE == 0)segE = 1;
      if (segF == 0)segF = 1;
      if (segG == 1)segG = 0;
      break;
    case 1:
      if (segA == 1)segA = 0;
      if (segB == 0)segB = 1;
      if (segC == 0)segC = 1;
      if (segD == 1)segD = 0;
      if (segE == 1)segE = 0;
      if (segF == 1)segF = 0;
      if (segG == 1)segG = 0;
      break;
    case 2:
      if (segA == 0)segA = 1;
      if (segB == 0)segB = 1;
      if (segC == 1)segC = 0;
      if (segD == 0)segD = 1;
      if (segE == 0)segE = 1;
      if (segF == 1)segF = 0;
      if (segG == 0)segG = 1;
      break;
    case 3:
      if (segA == 0)segA = 1;
      if (segB == 0)segB = 1;
      if (segC == 0)segC = 1;
      if (segD == 0)segD = 1;
      if (segE == 1)segE = 0;
      if (segF == 1)segF = 0;
      if (segG == 0)segG = 1;
      break;
    case 4:
      if (segA == 1)segA = 0;
      if (segB == 0)segB = 1;
      if (segC == 0)segC = 1;
      if (segD == 1)segD = 0;
      if (segE == 1)segE = 0;
      if (segF == 0)segF = 1;
      if (segG == 0)segG = 1;
      break;
    case 5:
      if (segA == 0)segA = 1;
      if (segB == 1)segB = 0;
      if (segC == 0)segC = 1;
      if (segD == 0)segD = 1;
      if (segE == 1)segE = 0;
      if (segF == 0)segF = 1;
      if (segG == 0)segG = 1;
      break;
    case 6:
      if (segA == 0)segA = 1;
      if (segB == 1)segB = 0;
      if (segC == 0)segC = 1;
      if (segD == 0)segD = 1;
      if (segE == 0)segE = 1;
      if (segF == 0)segF = 1;
      if (segG == 0)segG = 1;
      break;
    case 7:
      if (segA == 0)segA = 1;
      if (segB == 0)segB = 1;
      if (segC == 0)segC = 1;
      if (segD == 1)segD = 0;
      if (segE == 1)segE = 0;
      if (segF == 1)segF = 0;
      if (segG == 1)segG = 0;
      break;
    case 8:
      if (segA == 0)segA = 1;
      if (segB == 0)segB = 1;
      if (segC == 0)segC = 1;
      if (segD == 0)segD = 1;
      if (segE == 0)segE = 1;
      if (segF == 0)segF = 1;
      if (segG == 0)segG = 1;
      break;
    case 9:
      if (segA == 0)segA = 1;
      if (segB == 0)segB = 1;
      if (segC == 0)segC = 1;
      if (segD == 1)segD = 0;
      if (segE == 1)segE = 0;
      if (segF == 0)segF = 1;
      if (segG == 0)segG = 1;
      break;
  }
}

void switch_7seg() {
  if (segA == 0) digitalWrite(segmentPins[0], LOW); //A
  if (segA == 1) digitalWrite(segmentPins[0], HIGH); //A
  if (segB == 0) digitalWrite(segmentPins[1], LOW); //B
  if (segB == 1) digitalWrite(segmentPins[1], HIGH); //B
  if (segC == 0) digitalWrite(segmentPins[2], LOW); //C
  if (segC == 1) digitalWrite(segmentPins[2], HIGH); //C
  if (segD == 0) digitalWrite(segmentPins[3], LOW); //D
  if (segD == 1) digitalWrite(segmentPins[3], HIGH); //D
  if (segE == 0) digitalWrite(segmentPins[4], LOW); //E
  if (segE == 1) digitalWrite(segmentPins[4], HIGH); //E
  if (segF == 0) digitalWrite(segmentPins[5], LOW); //F
  if (segF == 1) digitalWrite(segmentPins[5], HIGH); //F
  if (segG == 0) digitalWrite(segmentPins[6], LOW); //G
  if (segG == 1) digitalWrite(segmentPins[6], HIGH); //G
}
