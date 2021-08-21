int a = 2;
int b = 3;
int c = 4, d = 5, e = 6, f = 7, g = 8;
int pin = 9;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(pin, INPUT);


}

void loop() {
  // put your main code here, to run repeatedly:


  //button starts
  if (digitalRead(pin) == HIGH) {
    while (digitalRead(pin) == HIGH) {
    }
    delay(250);
    // what button will do
    //_____________________

    Serial.println("hello world");

    //_____________________
  }
  //button ends
}
