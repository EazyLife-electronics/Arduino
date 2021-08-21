int sKy_ade = 5;
int gold = 2;
void setup() {
  Serial.begin(9600); 
  // put your setup code here, to run once:
  pinMode(gold, INPUT);



  if (sKy_ade == 1) {
    // what will happens if the if condition is met
    Serial.print("if");
  }
  else if (sKy_ade == 2) {
    // else if 1
    Serial.print("else if 1");
  }
  else if (sKy_ade == 5) {
    // else if 2
    Serial.print("else if 2");
  }
  else {
    // else this is what it will do
    Serial.print("else");
  }
}

void loop() {
  // put your main code here, to run repeatedly



  //button check
  if (digitalRead(gold) == HIGH) {
    // what button will do
    while (digitalRead(gold) == HIGH) {
      
    }
    //waiting for us to remove our hands
    delay(250);
    //avoid shanking hands
  }
  //button end




}
