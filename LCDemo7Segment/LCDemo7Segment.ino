//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,8);

/* we always wait a bit between updates of the display */
unsigned long delaytime=150;

void setup() {
  //we have already set the number of devices when we created the LedControl
  int devices=lc.getDeviceCount();
  //we have to init all devices in a loop
  for(int address=0;address<devices;address++) {
    /*The MAX72XX is in power-saving mode on startup*/
    lc.shutdown(address,false);
    /* Set the brightness to a medium values */
    lc.setIntensity(address,8);
    /* and clear the display */
    lc.clearDisplay(address);
  }
}


/*
 This method will display the characters for the
 word "Arduino" one after the other on digit 0. 
 */
void writeArduinoOn7Segment() {
  lc.setChar(0,0,'a',false);
  lc.setChar(0,1,'b',false);
  lc.setChar(0,2,'c',false);
  lc.setChar(0,3,'d',false);
  lc.setChar(0,4,'e',false);
  lc.setChar(0,5,'f',false);
  lc.setChar(0,6,'h',false);
  lc.setChar(0,7,'l',false);
  lc.setChar(1,0,'n',false);
  lc.setChar(1,1,'o',false);
  lc.setChar(1,2,'p',false);
  lc.setChar(1,3,'1',false);
  lc.setChar(1,4,'2',false);
  lc.setChar(1,5,'3',false);
  lc.setChar(1,6,'4',false);
  lc.setChar(1,7,'0',false);
} 

/*
  This method will scroll all the hexa-decimal
 numbers and letters on the display. You will need at least
 four 7-Segment digits. otherwise it won't really look that good.
 */
void scrollDigits() {
  for(int i=0;i<13;i++) {
    lc.setDigit(0,3,i,false);
    lc.setDigit(0,2,i+1,false);
    lc.setDigit(0,1,i+2,false);
    lc.setDigit(0,0,i+3,false);
    delay(delaytime);
  }
  lc.clearDisplay(0);
  delay(delaytime);
}

void loop() { 
  writeArduinoOn7Segment();
}
