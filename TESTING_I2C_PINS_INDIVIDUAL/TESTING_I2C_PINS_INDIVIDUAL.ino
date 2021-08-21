/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/

/*
//  NodeMCU I2C with Arduino IDE
//Introduction
//I2C (Inter-Integrated Circuit) is a serial bus interface connection protocol. It is also called as TWI (two-wire interface) since it uses only two wires for communication. Those two wires are SDA (serial data) and SCL (serial clock).
//
//I2C is an acknowledgment-based communication protocol i.e. transmitter checks for an acknowledgment from the receiver after transmitting data to know whether data is received by the receiver successfully.
//
//I2Cworks in two modes namely,
//
//Master mode
//Slave mode
//SDA (serial data) wire is used for data exchange between master and slave devices. SCL (serial clock) is used for the synchronous clock in between master and slave devices.
//
//The master device initiates communication with a slave device. The master device requires a slave device address to initiate a conversation with a slave device. The slave device responds to the master device when it is addressed by a master device.
//
//NodeMCU has I2C functionality support on its GPIO pins. Due to internal functionality on ESP-12E, we cannot use all its GPIOs for I2C functionality. So, do tests before using any GPIO for I2C applications.
//
// 
//
//Example
//Let’s write an Arduino sketch for NodeMCU as an I2C master device and Arduino sketch for Arduino Uno as an I2C slave device. The master device sends a hello string to the slave device and the slave device will send a hello string in response to the master device.
//
//Here, we are using
//
//Master Device: NodeMCU
//
//Slave Device: Arduino Uno
//
//Slave Device Address: 8
//
//The interfacing diagram is shown in the below figure
//
//NodeMCU Arduino I2C interface
//
//NodeMCU Arduino I2C interface
//
// 
//
//Arduino Sketch for NodeMCU (Master I2C Device)
//#include <Wire.h>
//
//void setup() {
// Serial.begin(9600); /* begin serial for debug */
// Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */
//}
//
//void loop() {
// Wire.beginTransmission(8); /* begin with device address 8 */
// Wire.write("Hello Arduino");  /* sends hello string */
// Wire.endTransmission();    /* stop transmitting */
//
// Wire.requestFrom(8, 13); /* request & read data of size 13 from slave */
// while(Wire.available()){
//    char c = Wire.read();
//  Serial.print(c);
// }
// Serial.println();
// delay(1000);
//}
//Arduino Sketch for Arduino Uno (Slave I2C Device)
//#include <Wire.h>
//
//void setup() {
// Wire.begin(8);                /* join i2c bus with address 8 */
// Wire.onReceive(receiveEvent); /* register receive event */
// Wire.onRequest(requestEvent); /* register request event */
// Serial.begin(9600);           /* start serial for debug */
//}
//
//void loop() {
// delay(100);
//}
//
//// function that executes whenever data is received from master
//void receiveEvent(int howMany) {
// while (0 <Wire.available()) {
//    char c = Wire.read();      /* receive byte as a character */
//    Serial.print(c);           /* print the character */
//  }
// Serial.println();             /* to newline */
//}
//
//// function that executes whenever data is requested from master
//void requestEvent() {
// Wire.write("Hello NodeMCU");  /*send string on request */
//}
//Output Window
//Output window of the serial monitor at Slave device (Arduino Uno)
//
//Arduino Slave output window
//
//Output window of the serial monitor at Master device (NodeMCU)
//
//Arduino output window of NodeMCU I2C master

 */

void setup(){
  Serial.begin(9600);
  analogWrite(LEDpin, 512);  /* set initial 50% duty cycle */
}

void loop(){
  uint16_t dutycycle =  analogRead(A0); /* read continuous POT and set PWM duty cycle according */
  if(dutycycle > 1023) dutycycle = 1023;/* limit dutycycle to 1023 if POT read cross it */
  Serial.print("Duty Cycle: ");  Serial.println(dutycycle);
  analogWrite(LEDpin, dutycycle);
  delay(100);
}
 
*/
bool mod = 0;
unsigned long tim = 0;
void setup() {
  pinMode(D0, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(D1, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(D2, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(D3, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(D4, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(D5, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(D6, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(D7, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(D8, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(D9, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(D10, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
}

// the loop function runs over and over again forever
void loop() {
    for (int i = 0; i < 1024; i++) {
      analogWrite(D0, i);
      delay(10);
    }
    for (int i = 1023; i > -1; i--) {
      analogWrite(D0, i);
      delay(10);
    }

    
    for (int i = 0; i < 1024; i++) {
      analogWrite(D1, i);
      delay(10);
    }
    for (int i = 1023; i > -1; i--) {
      analogWrite(D1, i);
      delay(10);
    }

    
    for (int i = 0; i < 1024; i++) {
      analogWrite(D2, i);
      delay(10);
    }
    for (int i = 1023; i > -1; i--) {
      analogWrite(D2, i);
      delay(10);
    }

    
    for (int i = 0; i < 1024; i++) {
      analogWrite(D3, i);
      delay(10);
    }
    for (int i = 1023; i > -1; i--) {
      analogWrite(D3, i);
      delay(10);
    }

    
    for (int i = 0; i < 1024; i++) {
      analogWrite(D4, i);
      delay(10);
    }
    for (int i = 1023; i > -1; i--) {
      analogWrite(D4, i);
      delay(10);
    }

    
    for (int i = 0; i < 1024; i++) {
      analogWrite(D5, i);
      delay(10);
    }
    for (int i = 1023; i > -1; i--) {
      analogWrite(D5, i);
      delay(10);
    }

    
    for (int i = 0; i < 1024; i++) {
      analogWrite(D6, i);
      delay(10);
    }
    for (int i = 1023; i > -1; i--) {
      analogWrite(D6, i);
      delay(10);
    }

    
    for (int i = 0; i < 1024; i++) {
      analogWrite(D7, i);
      delay(10);
    }
    for (int i = 1023; i > -1; i--) {
      analogWrite(D7, i);
      delay(10);
    }

    
    for (int i = 0; i < 1024; i++) {
      analogWrite(D8, i);
      delay(10);
    }
    for (int i = 1023; i > -1; i--) {
      analogWrite(D8, i);
      delay(10);
    }

    
    for (int i = 0; i < 1024; i++) {
      analogWrite(D9, i);
      delay(10);
    }
    for (int i = 1023; i > -1; i--) {
      analogWrite(D9, i);
      delay(10);
    }

    
    for (int i = 0; i < 1024; i++) {
      analogWrite(D10, i);
      delay(10);
    }
    for (int i = 1023; i > -1; i--) {
      analogWrite(D10, i);
      delay(10);
    }

    
}
