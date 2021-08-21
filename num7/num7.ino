#include <Wire.h>
#include <RTC.h>

static DS1307 RTC;
int digitpin[8]={11, 10, 9, 8, 12, 13, A0, A1}, segmentpin[8]={1, 2, 5, 6, 3, 4, 7, 0}, digiint[8];
String digistring[8], Sdigit = "", alpha[8];
String dy, mo, yr;
void setup() {
  // put your setup code here, to run once:
RTC.begin();
}

void loop() {
  dy = String (RTC.getDay());
  mo = String (RTC.getMonth());
  yr = String (RTC.getYear());
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
    yr = "0000";
  }
  else if (yr.toInt() < 10) {
    yr = "000" + yr;
  }
  else if (yr.toInt() < 100) {
    yr = "00" + yr;
  }
  else if (yr.toInt() < 1000) {
    yr = "0" + yr;
  }
  Sdigit = dy + mo + yr;
  for (int i = 0; i < 8; i++) {
    String j = Sdigit.substring(i, i + 1);
    digiint[i] = j.toInt();
  }
  for (int i = 0; i < 8; i++) {
    digistring[i] = NUM7(digiint[i]);
  }

  for (int i = 0; i < 8; i++) {
    if (i != 0) {
      digitalWrite(segmentpin[i - 1], LOW);
    }
    else {
      digitalWrite(segmentpin[7], LOW);
    }
    digitalWrite(segmentpin[i], HIGH);

    for (int i = 0; i < 8; i++) {
      if (i != 0) {
        digitalWrite(digitpin[i - 1], LOW);
      }
      else {
        digitalWrite(digitpin[7], LOW);
      }
      int check = digit(i);
      if (check == 1) {
        digitalWrite(digitpin[i], LOW);
      }
      else {
        digitalWrite(digitpin[i], HIGH);
      }
    }
  }
}

String NUM7(int i) {
  switch (i) {
    case 0:
      return "abcdef";
      break;

    case 1:
      return "bc";
      break;

    case 2:
      return "abdeg";
      break;

    case 3:
      return "abcdg";
      break;

    case 4:
      return "bcfg";
      break;

    case 5:
      return "acdfg";
      break;

    case 6:
      return "acdefg";
      break;

    case 7:
      return "abc";
      break;

    case 8:
      return "abcdefg";
      break;

    case 9:
      return "abcdfg";
      break;
  }
}

int digit(int i) {
  String j = digistring[i];
  if (j.indexOf(alpha[i]) > 0) {
    return 1;
  }
  else {
    return 0;
  }
}
