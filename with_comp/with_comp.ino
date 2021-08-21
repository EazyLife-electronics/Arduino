// Including the required Arduino libraries
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
#define MAX_DEVICES 3
#define CS_PIN 10

int count = 0;
// Create a new instance of the MD_Parola class with hardware SPI connection
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
unsigned long fmillis=0;
void setup() {
  // Intialize the object
  myDisplay.begin();

  // Set the intensity (brightness) of the display (0-15)
  myDisplay.setIntensity(8);

  // Clear the display
  myDisplay.displayClear();

  myDisplay.displayScroll("D_EazyLife Electronics", PA_CENTER, PA_SCROLL_LEFT, 100);
}

void loop() {
  if (myDisplay.displayAnimate()) {
    myDisplay.displayReset();
    if (millis()>fmillis){
      fmillis=millis()+1000;
      count++;
    }
    String ade=String(count);
    myDisplay.print(ade);
    delay(1000);
    myDisplay.displayClear();
    myDisplay.displayScroll("count =>", PA_CENTER, PA_SCROLL_LEFT, 100);
  }
}
