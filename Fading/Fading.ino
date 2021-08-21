int Pin = 3;    // LED connected to digital pin 9
int x = 0;
int done = true;
void setup() {
  pinMode(Pin, OUTPUT);
}

void loop() {
  delay(10);
  if (done == true) {
    x++;
    if (x >= 255) {
      done=false;
    }
  }
  if (done == false) {
    x--;
    if (x <=0) {
      done=true;
    }
  }
  analogWrite(Pin, x);//0-255
}
