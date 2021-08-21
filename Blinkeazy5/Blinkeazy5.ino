
int paul[5]={5,5,5,5,5};
void setup() {
  Serial.begin(9600);
  Serial.print(paul[0]);
  Serial.println(", ");
  Serial.print(paul[1]);
  Serial.println(", ");
  Serial.print(paul[2]);
  Serial.println(", ");
  Serial.print(paul[3]);
  Serial.println(", ");
  Serial.println(paul[4]);
  paul[0]={0};
  paul[1]={1};
  paul[2]={2};
  paul[3]={3};
  paul[4]={4};
  Serial.print(paul[0]);
  Serial.println(", ");
  Serial.print(paul[1]);
  Serial.println(", ");
  Serial.print(paul[2]);
  Serial.println(", ");
  Serial.print(paul[3]);
  Serial.println(", ");
  Serial.println(paul[4]);
  
}

// the loop function runs over and over again forever
void loop() {
}
