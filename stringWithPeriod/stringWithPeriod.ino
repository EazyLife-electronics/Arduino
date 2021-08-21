
#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment controller object

#define MAX_NUMBER_STRINGS 12
#define MAX_STRING_SIZE 8
char testStrings[8];

#define PATTERN_CHANGE_TIME 1000
unsigned long timer = millis() - PATTERN_CHANGE_TIME;
byte testStringsPos = 0;

void setup() {
  
  byte numDigits = 8; 
  byte digitPins[] = {12, 13, 11, 10, 9, 8, 6, 7};
  byte segmentPins[] = {3, 4, A0, A1, 1, 2, 5};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = true; // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  sevseg.setBrightness(90);

  // Adds set of test strings with periods in various places
  strcpy(testStrings, "ARDUINO");
    sevseg.setChars(testStrings);
}

void loop() {


  sevseg.refreshDisplay(); // Must run repeatedly
}

/// END ///
