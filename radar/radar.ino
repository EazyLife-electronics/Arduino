#include <Servo.h>
Servo Direction;
unsigned long Distance, Facing, mapAngle, box=50;
unsigned long compass;

void setup() {
  Serial.begin(9600);
  Direction.attach(9);
}

void loop() {
  Facing = compass;
  for (int ang = 0; ang < 180; ang++) {
    Direction.write(ang);
    mapAngle = Facing + ang;
    if (mapAngle > 360) {
      mapAngle -= 360;
    }
    else if (mapAngle < 0) {
      mapAngle += 360;
    }
    Distance = Ping(2, 3);
    
    Serial.print(Distance);
    Serial.print("cm");
    Serial.println();
    delay(100);
  }
}

unsigned long Ping(int TriggerPin, int EchoPin) {
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(11);
  digitalWrite(TriggerPin, LOW);
  unsigned long duration = pulseIn(EchoPin, HIGH);
  return duration / 58;
}
