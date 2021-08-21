
const int echoPin = 2;
const int triggerPin = 3;
const int motor = 5;
const int butt = 6;
const int ledPin =  LED_BUILTIN;// the number of the LED pin
bool state = 0;
long duration, cm;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motor, OUTPUT);
  pinMode(butt, INPUT_PULLUP);
  digitalWrite(motor, LOW);
}

void loop() {
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(11);
  digitalWrite(triggerPin, LOW);
  // The echo pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  delay(100);
  if (digitalRead(butt) == LOW) {
    while (digitalRead(butt) == LOW) {}
    delay(100);
    state = !state;
  }
  if (!state) {
    digitalWrite(motor, LOW);
  }
  else {
    if (cm <= 30) {
      digitalWrite(motor, LOW);
    }
    else {
      digitalWrite(motor, HIGH);
    }
  }
  digitalWrite(ledPin, state);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
