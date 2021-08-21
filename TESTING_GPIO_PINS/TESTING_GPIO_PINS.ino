/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/

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
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(D0, LOW);   // Turn the LED on (Note that LOW is the voltage level
  digitalWrite(D1, LOW);     // Initialize the LED_BUILTIN pin as an LOW
  digitalWrite(D2, LOW);     // Initialize the LED_BUILTIN pin as an LOW
  digitalWrite(D3, LOW);     // Initialize the LED_BUILTIN pin as an LOW
  digitalWrite(D4, LOW);     // Initialize the LED_BUILTIN pin as an LOW
  digitalWrite(D5, LOW);     // Initialize the LED_BUILTIN pin as an LOW
  digitalWrite(D6, LOW);     // Initialize the LED_BUILTIN pin as an LOW
  digitalWrite(D7, LOW);     // Initialize the LED_BUILTIN pin as an LOW
  digitalWrite(D8, LOW);     // Initialize the LED_BUILTIN pin as an output
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(500);                      // Wait for a second
  digitalWrite(D0, HIGH);  // Turn the LED off by making the voltage HIGH
  digitalWrite(D1, HIGH);     // Initialize the LED_BUILTIN pin as an HIGH
  digitalWrite(D2, HIGH);     // Initialize the LED_BUILTIN pin as an HIGH
  digitalWrite(D3, HIGH);     // Initialize the LED_BUILTIN pin as an HIGH
  digitalWrite(D4, HIGH);     // Initialize the LED_BUILTIN pin as an HIGH
  digitalWrite(D5, HIGH);     // Initialize the LED_BUILTIN pin as an HIGH
  digitalWrite(D6, HIGH);     // Initialize the LED_BUILTIN pin as an HIGH
  digitalWrite(D7, HIGH);     // Initialize the LED_BUILTIN pin as an HIGH
  digitalWrite(D8, HIGH);     // Initialize the LED_BUILTIN pin as an output
  delay(500);                      // Wait for two seconds (to demonstrate the active low LED)
}
