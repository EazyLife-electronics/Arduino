int MA = 5, MB = 6;
int DA = 4, DB = 7;
int FB = A0, RL = A1;
int FB_Val, RL_Val;
void setup() {
  Serial.begin(9600);
  pinMode (MA, OUTPUT);
  pinMode (MB, OUTPUT);
  pinMode (DA, OUTPUT);
  pinMode (DB, OUTPUT);
  pinMode (FB, INPUT);
  pinMode (RL, INPUT);
}

void loop() {
  // get the analog read of the consoles
  
  FB_Val = analogRead(FB);
  RL_Val = analogRead(RL);

  if (FB_Val > 500 && FB_Val < 523 && RL_Val > 500 && RL_Val < 523) {
    Stop();
  }
  else if (RL_Val > 500 && RL_Val < 523 && FB_Val > 523) {
    Forward();
  }
  else if (RL_Val > 500 && RL_Val < 523 && FB_Val < 500) {
    Backward();
  }
  else if (FB_Val > 500 && FB_Val < 523 && RL_Val < 500) {
    Rot_Left();
  }
  else if (FB_Val > 500 && FB_Val < 523 && RL_Val > 523) {
    Rot_Right();
  }
  else if (RL_Val > 523 && FB_Val > 523) {
    Forward_Right();
  }
  else if (RL_Val < 500 && FB_Val > 523) {
    Forward_Left();
  }
  else if (RL_Val > 523 && FB_Val < 500) {
    Backward_Right();
  }
  else if (RL_Val < 500 && FB_Val < 500) {
    Backward_Left();
  }
}




void Stop() {
  digitalWrite(DA, 0);
  digitalWrite(DB, 0);
  analogWrite(MA, 0);
  analogWrite(MB, 0);
  Serial.println("Stopped");
}
void Forward() {
  digitalWrite(DA, 1);
  digitalWrite(DB, 1);
  int lev = map(FB_Val, 523, 1023, 1, 255);
  analogWrite(MA, lev);
  analogWrite(MB, lev);
  Serial.print("lev = ");
  Serial.println(lev);
}
void Backward() {
  digitalWrite(DA, 0);
  digitalWrite(DB, 0);
  int lev = map(FB_Val, 500, 0, 1, 255);
  analogWrite(MA, lev);
  analogWrite(MB, lev);
  Serial.print("lev = ");
  Serial.println(lev);
}
void Rot_Left() {
  digitalWrite(DA, 0);
  digitalWrite(DB, 1);
  int lev = map(RL_Val, 500, 0, 1, 255);
  analogWrite(MA, lev);
  analogWrite(MB, lev);
  Serial.print("lev = ");
  Serial.println(lev);
}
void Rot_Right() {
  digitalWrite(DA, 1);
  digitalWrite(DB, 0);
  int lev = map(RL_Val, 523, 1023, 1, 255);
  analogWrite(MA, lev);
  analogWrite(MB, lev);
  Serial.print("lev = ");
  Serial.println(lev);
}

void Forward_Right() {
  digitalWrite(DA, 1);
  digitalWrite(DB, 1);
  int levFB = map(FB_Val, 523, 1023, 1, 255);
  int levRL = map(RL_Val, 523, 1023, 1, 255);
  int levA = map(FB_Val, 523, 1023, levRL, levFB);
  int levB = map(levA, 0, 255, levA,0);
  analogWrite(MA, levA);
  analogWrite(MB, levB);
  Serial.print("levA = ");
  Serial.print(levA);
  Serial.print(", levB = ");
  Serial.println(levB);
}

void Forward_Left() {
  digitalWrite(DA, 1);
  digitalWrite(DB, 1);
  int levFB = map(FB_Val, 523, 1023, 1, 255);
  int levRL = map(RL_Val, 500, 0, 1, 255);
  int levB = map(FB_Val, 523, 1023, levRL, levFB);
  int levA = map(FB_Val, 500, 0, levRL, levFB);
  analogWrite(MA, levA);
  analogWrite(MB, levB);
  Serial.print("levA = ");
  Serial.print(levA);
  Serial.print(", levB = ");
  Serial.println(levB);
}

void Backward_Right() {
  digitalWrite(DA, 0);
  digitalWrite(DB, 0);
  int levFB = map(FB_Val, 500, 0, 1, 255);
  int levRL = map(RL_Val, 523, 1023, 1, 255);
  int levB = map(FB_Val, 500, 0, levRL, levFB);
  int levA = map(FB_Val, 523, 1023, levRL, levFB);
  analogWrite(MA, levA);
  analogWrite(MB, levB);
  Serial.print("levA = ");
  Serial.print(levA);
  Serial.print(", levB = ");
  Serial.println(levB);
}

void Backward_Left() {
  digitalWrite(DA, 0);
  digitalWrite(DB, 0);
  int levFB = map(FB_Val, 500, 0, 1, 255);
  int levRL = map(RL_Val, 500, 0, 1, 255);
  int levA = map(FB_Val, 500, 0, levRL, levFB);
  int levB = map(FB_Val, 500, 0, levRL, levFB);
  analogWrite(MA, levA);
  analogWrite(MB, levB);
  Serial.print("levA = ");
  Serial.print(levA);
  Serial.print(", levB = ");
  Serial.println(levB);
}
