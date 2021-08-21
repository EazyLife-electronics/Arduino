
#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment controller object

bool bt = true;
String dh, hr, mi;
char testStrings[8], char_array[9];
String SDIGIT;

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {A0, A1, A3, 2};
  byte segmentPins[] = {13, 12, 11, 10, 9, 8, 7};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = true; // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
               updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
  SDIGIT = "EAZY";
  SDIGIT.toCharArray(char_array, 5);
  strcpy(testStrings, char_array);
  sevseg.setChars(testStrings);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(3,OUTPUT);
  analogWrite(6,255);
  analogWrite(5,255);
  analogWrite(3,255);
}

void loop() {
  sevseg.refreshDisplay();
}
