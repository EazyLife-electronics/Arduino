#include <Wire.h>
#include <RTC.h>
static DS1307 RTC;

#include "DHT.h"
#define DHTPIN 9
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include "LedControl.h"
LedControl lc = LedControl(12, 11, 10, 2);

unsigned long set_times = millis(), timer = millis(), blink_time = millis(), up_times = millis();
int set_things = A3, up_things = A2, set_things1 = A1, up_things1 = A0, set_things2 = 8, up_things2 = 7, led = 13, which_one = 0, pressed = 0, led_blink = 0;
String dh, hr, mi, dy, mo, yr;
char char_array[17];
String SDIGIT;
long UP = 0;
void setup() {
  RTC.begin();

  dht.begin();

  pinMode(led, OUTPUT);
  pinMode(set_things, INPUT);
  pinMode(up_things, INPUT);

  int devices = lc.getDeviceCount();
  for (int i = 0; i < devices; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 8);
    lc.clearDisplay(i);
  }
}

void loop() {

  if (millis() > timer) {
    timer = millis() + 1000;
    getAndDisplay();
  }
  if (digitalRead(up_things) == HIGH) {
    pressed = 0;
    while (digitalRead(up_things) == HIGH) {
      if (digitalRead(set_things) == HIGH) {
        while (digitalRead(set_things) == HIGH) {
          if (millis() > timer) {
            timer = millis() + 1000;
            getAndDisplay();
          }
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
      }
    }
    if (pressed == 0) {
      UP = RTC.getHours() + 1;
      if (UP > 23) {
        UP = 0;
      }
      RTC.setHours(UP);
    }
  }
  else if (digitalRead(set_things) == HIGH) {
    pressed = 0;
    while (digitalRead(set_things) == HIGH) {
      if (digitalRead(up_things) == HIGH) {
        while (digitalRead(up_things) == HIGH) {
          if (millis() > timer) {
            timer = millis() + 1000;
            getAndDisplay();
          }
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
      }
    }
    if (pressed == 0) {
      UP = RTC.getMinutes() + 1;
      if (UP > 59) {
        UP = 0;
      }
      RTC.setMinutes(UP);
    }
  }
  else if (digitalRead(up_things1) == HIGH) {
    pressed = 0;
    while (digitalRead(up_things1) == HIGH) {
      if (digitalRead(set_things1) == HIGH) {
        while (digitalRead(set_things1) == HIGH) {
          if (millis() > timer) {
            timer = millis() + 1000;
            getAndDisplay();
          }
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
      }
    }
    if (pressed == 0) {
      UP = RTC.getDay() + 1;
      if (UP > 31) {
        UP = 1;
      }
      RTC.setDay(UP);
    }
  }
  else if (digitalRead(set_things1) == HIGH) {
    pressed = 0;
    while (digitalRead(set_things1) == HIGH) {
      if (digitalRead(up_things) == HIGH) {
        while (digitalRead(up_things) == HIGH) {
          if (millis() > timer) {
            timer = millis() + 1000;
            getAndDisplay();
          }
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
      }
    }
    if (pressed == 0) {
      UP = RTC.getMonth() + 1;
      if (UP > 12) {
        UP = 1;
      }
      RTC.setMonth(UP);
    }
  }
  else if (digitalRead(up_things2) == HIGH) {
    while (digitalRead(up_things2) == HIGH) {
      if (millis() > timer) {
        timer = millis() + 1000;
        getAndDisplay();
      }
    }
    UP = RTC.getYear() + 1;
    if (UP > 9999) {
      UP = 1000;
    }
    RTC.setYear(UP);
  }
  else if (digitalRead(set_things2) == HIGH) {
    while (digitalRead(set_things2) == HIGH) {
      if (millis() > timer) {
        timer = millis() + 1000;
        getAndDisplay();
      }
    }
    UP = RTC.getYear() - 1;
    if (UP < 1000) {
      UP = 9999;
    }
    RTC.setYear(UP);
  }
}


void getAndDisplay() {
  int ddd = dht.readTemperature();
  dh = String (ddd);
  hr = String (RTC.getHours());
  mi = String (RTC.getMinutes());
  dy = String (RTC.getDay());
  mo = String (RTC.getMonth());
  yr = String (RTC.getYear());
  if (dh == "0") {
    dh = "  ";
  }
  else if (dh.toInt() < 10) {
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
  if (dh.toInt() > 99) {
    SDIGIT = hr + mi + dh + "C" + dy + mo + yr;
  }
  else {
    SDIGIT = hr + mi + dh + "C " + dy + mo + yr;
  }
  SDIGIT.toCharArray(char_array, 17);
  for (int i = 0; i < 8; i++) {
    lc.setChar(0, i, char_array[i], false);
  }
  for (int i = 0, j = 8; i < 8; i++, j++) {
    lc.setChar(1, i, char_array[j], false);
  }
  if (led_blink == 1) {
    led_blink = 0;
    digitalWrite(led, HIGH);
  }
  else {
    led_blink = 1;
    digitalWrite(led, LOW);
  }
}
