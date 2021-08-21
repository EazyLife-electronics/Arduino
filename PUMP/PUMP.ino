#include <LiquidCrystal.h>
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int echoPin = 9;
const int triggerPin = 10;
const int pump = 8;
int ppp = 0;

// establish variables for duration of the ping, and the distance result
// in inches and centimeters:
long duration, cm, tankHeight = 35;

void setup() {
  lcd.begin(16, 2);
  lcd.home();
  lcd.print("   AUTOMATIC");
  lcd.setCursor(0, 1);
  lcd.print(" PUMPING SYSTEM");
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pump, OUTPUT);
  digitalWrite(pump, LOW);
  delay(10000);
}

void loop() {
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(triggerPin, LOW);

  // The echo pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  delay(100);
  int displayP = constrain(map(cm, 5, tankHeight, 100, 0), 0, 100);
  lcd.clear();
  lcd.home();
  lcd.print("Tank Lev = ");
  lcd.print(displayP);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Pump ");
  if (displayP >= 100) {
  digitalWrite(pump, LOW);
  ppp=0;
  }
  else if (displayP < 40) {
  digitalWrite(pump, HIGH);
  ppp=1;
  }
  if (ppp == 0) {
  lcd.print("OFF");
  }
  else{
  lcd.print("ON");
  }
  lcd.setCursor(10, 1);
  lcd.print("TH=");
  lcd.print(tankHeight);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
