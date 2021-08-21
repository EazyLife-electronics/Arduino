int a = 2, b = 3, c = 4;
int tade = 0;
int paul[5]={45,2,5,6,8};
void setup() {
  Serial.begin(9600);
  pinMode(a, INPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
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
