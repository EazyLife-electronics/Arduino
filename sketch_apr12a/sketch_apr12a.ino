
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#include "HX711.h"

#include <LiquidCrystal.h>

const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned long LCD = 0;
int D = 1;

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 4;
const int LOADCELL_SCK_PIN = 5;
const int echPin = 7, trigPin = 6;
unsigned long duration;



HX711 scale;
float BMI = 0.0, cm, cmd, inches;

void setup() {

  mlx.begin();
  lcd.begin(16, 4);
  lcd.clear();
  lcd.home();
  lcd.print(" AUTOMATIC BODY");
  lcd.setCursor(0,1);
  lcd.print("MEASURING DEVICE");
  delay(2000);
  pinMode(echPin, INPUT);
  pinMode(trigPin, OUTPUT);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(2600.f);
  scale.tare();  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echPin, HIGH);
  cmd = duration / 29 / 2;
}

void loop() {
  scale.power_down();
  delay(1000);
  scale.power_up();

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echPin, HIGH);
  cm = duration / 29 / 2;
  cm = cmd - cm;
  lcd.clear();
  lcd.home();
  lcd.print("Height = ");
  lcd.print(cm / 100.0);
  lcd.print(" m");
  lcd.setCursor(0, 1);
  lcd.print("weight = ");
  lcd.println(scale.get_units(10) / 10.0,1);
  lcd.setCursor(0, 2);
  lcd.print("Temp = ");
  lcd.print(mlx.readObjectTempC());
  lcd.print(" *C");
  lcd.setCursor(0, 3);
  lcd.print("BMI = ");
  BMI = cm / 100.0;
  BMI = (scale.get_units(10) /10.0)/ pow(BMI, 2);
  lcd.print(BMI);
  lcd.print(" Kg/m*");
}
