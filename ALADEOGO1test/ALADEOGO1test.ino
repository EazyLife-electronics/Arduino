#include <Wire.h>
#include <RTC.h>

static DS1307 RTC;
#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment controller object

#include "DHT.h"
#define DHTPIN 0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

unsigned long set_times = millis(), timer = millis(), blink_time = millis(), up_times = millis();
int set_things = A3, up_things = A2, which_one = 0, UP = 0, pressed = 0;
bool bt = true;
String dh, hr, mi;
char testStrings[8], char_array[9];
String SDIGIT;

void setup() {
  RTC.begin();

  dht.begin();

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
    SDIGIT = hr + mi + dh + "C";
    SDIGIT.toCharArray(char_array, 9);
    strcpy(testStrings, char_array);
    sevseg.setChars(testStrings);
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
        UP = RTC.getHours() - 1;
        if (UP < 0) {
          UP = 23;
        }
        RTC.setHours(UP);
      }
      if (millis() > timer) {
        timer = millis() + 1000;
        getAndDisplay();
        SDIGIT = hr + mi + dh + "C";
        SDIGIT.toCharArray(char_array, 9);
        strcpy(testStrings, char_array);
        sevseg.setChars(testStrings);
      }
      sevseg.refreshDisplay();
    }
    if (pressed == 0) {
      UP = RTC.getHours() + 1;
      if (UP > 23) {
        UP = 0;
      }
      RTC.setHours(UP);
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
        UP = RTC.getMinutes() - 1;
        if (UP < 0) {
          UP = 59;
        }
        RTC.setMinutes(UP);
      }
      if (millis() > timer) {
        timer = millis() + 1000;
        getAndDisplay();
        SDIGIT = hr + mi + dh + "C";
        SDIGIT.toCharArray(char_array, 9);
        strcpy(testStrings, char_array);
        sevseg.setChars(testStrings);
      }
      sevseg.refreshDisplay();
    }
    if (pressed == 0) {
      UP = RTC.getMinutes() + 1;
      if (UP > 59) {
        UP = 0;
      }
      RTC.setMinutes(UP);
    }
  }
}


void getAndDisplay() {
  int ddd = dht.readTemperature();
  dh = String (ddd);
  hr = String (RTC.getHours());
  mi = String (RTC.getMinutes());
  if (dh == "0") {
    dh = "   ";
  }
  else if (dh.toInt() < 10) {
    dh = "  " + dh;
  }
  else if (dh.toInt() < 100) {
    dh = " " + dh;
  }
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
}
