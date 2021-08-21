#include <Wire.h>
#include <RTC.h>

static DS1307 RTC;
#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment controller object

unsigned long set_times = millis(), timer = millis(), blink_time = millis(), up_times = millis();
int set_things = A3, up_things = A2, which_one = 0, UP = 0, pressed = 0;
String dy, mo, yr;

String SDIGIT;

void setup() {
  RTC.begin();

  byte numDigits = 8;
  byte digitPins[] = {8, 9, 10, 11, 12, 13, A0, A1};
  byte segmentPins[] = {1, 2, 3, 4, 5, 6, 7};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = true; // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
               updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);

  pinMode(set_things, INPUT);
  pinMode(up_things, INPUT);
}

void loop() {

  if (millis() > timer) {
    timer = millis() + 1000;
    getAndDisplay();
    SDIGIT = dy + mo + yr;
    sevseg.setNumber(SDIGIT.toInt());
  }
  sevseg.refreshDisplay();

  if (digitalRead(up_things) == HIGH) {
    pressed = 0;
    while (digitalRead(up_things) == HIGH) {
      if (digitalRead(set_things) == HIGH) {
        while (digitalRead(set_things) == HIGH) {
          sevseg.refreshDisplay();
        }
        pressed = 1;
        UP = RTC.getDay() - 1;
        if (UP < 1) {
          UP = 31;
        }
        RTC.setDay(UP);
      }
      if (millis() > timer) {
        timer = millis() + 1000;
        getAndDisplay();
        SDIGIT = dy + mo + yr;
        sevseg.setNumber(SDIGIT.toInt());
      }
      sevseg.refreshDisplay();
    }
    if (pressed == 0) {
      UP = RTC.getDay() + 1;
      if (UP > 31) {
        UP = 1;
      }
      RTC.setDay(UP);
    }
  }
  if (digitalRead(set_things) == HIGH) {
    pressed = 0;
    while (digitalRead(set_things) == HIGH) {
      if (digitalRead(up_things) == HIGH) {
        while (digitalRead(up_things) == HIGH) {
          sevseg.refreshDisplay();
        }
        pressed = 1;
        UP = RTC.getMonth() - 1;
        if (UP < 1) {
          UP = 12;
        }
        RTC.setMonth(UP);
      }
      if (millis() > timer) {
        timer = millis() + 1000;
        getAndDisplay();
        SDIGIT = dy + mo + yr;
        sevseg.setNumber(SDIGIT.toInt());
      }
      sevseg.refreshDisplay();
    }
    if (pressed == 0) {
      UP = RTC.getMonth() + 1;
      if (UP > 12) {
        UP = 1;
      }
      RTC.setMonth(UP);
    }
  }
}


void getAndDisplay() {
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
}
