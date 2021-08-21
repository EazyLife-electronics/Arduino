#include <Servo.h>
Servo Scan;
unsigned long Distance, mapAngle, box = 30, hundred, moveLeft, glideLeft, moveRight, glideRight, moveFront, per;
int Direction, velocity = 200;
bool glide;
void setup() {
  Serial.begin(9600);
  Scan.attach(8);
}

void loop() {
  Range();
  Decide();
  Drive();
  delay(1000);
}

void Range() {
  for (int ang = 0; ang < 181; ang++) {
    long period = (box + 1) * 60;
    Distance = Ping(2, 3, period);
    Scan.write(ang);
    Serial.println(ang);
    per = per + map(Distance, 0, hundred, 0, 100);
    if (ang == 36) {
      moveLeft = per / 36;
      per = 0;
    }
    else if (ang == 72) {
      glideLeft = per / 36;
      per = 0;
    }
    else if (ang == 108) {
      moveFront = per / 36;
      per = 0;
    }
    else if (ang == 144) {
      glideRight = per / 36;
      per = 0;
    }
    else if (ang == 180) {
      moveRight = per / 36;
      per = 0;
    }
  }
}
void Decide() {
  if (moveFront >= 98) {
    glide = 0;
    Direction = 0;
  }
  else {
    if (glideRight >= 98 || glideLeft >= 98) {
      glide = 1;
      if (glideRight >= glideLeft) {
        Direction = 1;
      }
      else {
        Direction = -1;
      }
    }
    else if (moveRight >= 98 && glide == 0) {
      Direction = 2;
    }
    else if (moveLeft >= 98 && glide == 0) {
      Direction = -2;
    }
    else {
      Direction = 3;
    }
  }
}
void Drive() {
  Scan.write(90);
  Distance = Ping(2, 3, 240);
  switch (Direction) {
    case 0:
      Serial.println("DFront");
      while (Distance >= 3 || Distance == 0) {
        dir(5, 4, 1, velocity, 100);
        dir(6, 7, 1, velocity, 100);
        Distance = Ping(2, 3, 240);
      }

      break;
    case 1:
      Serial.println("GRight");
      while (Distance >= 3 || Distance == 0) {
        dir(5, 4, 1, velocity, 100);
        dir(6, 7, 1, velocity, 50);
        Distance = Ping(2, 3, 240);
      }
      break;
    case -1:
      Serial.println("GLeft");
      while (Distance >= 3 || Distance == 0) {
        dir(5, 4, 1, velocity, 50);
        dir(6, 7, 1, velocity, 100);
        Distance = Ping(2, 3, 240);
      }
      break;
    case 2:
      Serial.println("DRight");
      while (Distance >= 3 || Distance == 0) {
        dir(5, 4, 1, velocity, 50);
        dir(6, 7, 0, velocity, 50);
        Distance = Ping(2, 3, 240);
      }
      break;
    case -2:
      Serial.println("DLeft");
      while (Distance >= 3 || Distance == 0) {
        dir(5, 4, 0, velocity, 50);
        dir(6, 7, 1, velocity, 50);
        Distance = Ping(2, 3, 240);
      }
      break;
    case 3:
      Serial.println("Back");
      while (Distance >= 3 || Distance == 0) {
        dir(5, 4, 1, velocity, 50);
        dir(6, 7, 0, velocity, 50);
      }
      break;
  }
}

void dir(int motorPin, int directionPin, bool direct, int duty, int percent) {
  pinMode(motorPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  if (direct == 1) {
    digitalWrite(directionPin, HIGH);
    int cac = ((100 - percent) / 100) * duty;
    analogWrite(motorPin, cac);
  }
  else if (direct == 0) {
    digitalWrite(directionPin, LOW);
    int cac = (percent / 100) * duty;
    analogWrite(motorPin, cac);
  }
}

unsigned long Ping(int TriggerPin, int EchoPin, unsigned long timeOut) {
  unsigned long duration;
  if (timeOut > 0) {
    pinMode(TriggerPin, OUTPUT);
    pinMode(EchoPin, INPUT);
    digitalWrite(TriggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TriggerPin, HIGH);
    delayMicroseconds(11);
    digitalWrite(TriggerPin, LOW);
    duration = pulseIn(EchoPin, HIGH, timeOut);
  }
  else {
    pinMode(TriggerPin, OUTPUT);
    pinMode(EchoPin, INPUT);
    digitalWrite(TriggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TriggerPin, HIGH);
    delayMicroseconds(11);
    digitalWrite(TriggerPin, LOW);
    duration = pulseIn(EchoPin, HIGH);
  }
  return duration / 58;
}

float cosd(float calc_cos) {
  return cos(calc_cos * 0.017453);
}

float acosd(float calc_acos) {
  return acos(calc_acos) * 57.296;
}
