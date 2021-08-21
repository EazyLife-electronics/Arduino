
long measure1, measure2, measure3, measure4, measure5, measure6;

void setup() {
  Serial.begin(9600);
}

void loop() {
  measure1 = Ping(2, 3);
  measure2 = Ping(4, 5);
  measure3 = Ping(6, 7);
  measure4 = Ping(8, 9);
  measure5 = Ping(10, 11);
  Serial.print(measure1);
  Serial.print("cm, ");
  Serial.print(measure2);
  Serial.print("cm, ");
  Serial.print(measure3);
  Serial.print("cm, ");
  Serial.print(measure4);
  Serial.print("cm, ");
  Serial.print(measure5);
  Serial.print("cm");
  Serial.println();
  delay(100);
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
