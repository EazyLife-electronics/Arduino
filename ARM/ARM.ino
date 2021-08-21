
#include <Servo.h>

Servo myservo;

const int echoPin = A0;
const int triggerPin = A2;
const int th = A3;
const int buzz = 4;

long duration, cm, HEIGHT = 35, treshold;

void setup() {
  Serial.begin(9600);
  myservo.attach(A5);
  pinMode(buzz, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(th, INPUT);
  myservo.write(30);
  delay(100);
}

void loop() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(triggerPin, LOW);

  treshold = constrain(map(analogRead(th), 0, 1024, HEIGHT, 0), 0, HEIGHT);
  duration = pulseIn(echoPin, HIGH);

  cm = microsecondsToCentimeters(duration);
  Serial.println(cm);
  Serial.println(treshold);
  if (cm <= treshold) {
    digitalWrite(buzz, HIGH);
    myservo.write(180);
    delay(500);
    digitalWrite(buzz, LOW);
    delay(10);
    for (int i = 180; i > 30; i--) {
      myservo.write(i);
      delay(4);
    }
  }
  else{
    myservo.write(30);
  }
  delay(50);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
