#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(6, 4, 2, 5, 7, A7);//(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO)

#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8); //(rs, en, d4, d5, d6, d7)

byte squa[8] = {
  0b01110,
  0b10001,
  0b00110,
  0b11000,
  0b11111,
  0b00000,
  0b00000,
  0b00000
};




float V = 0, U = 0, R = 0.50;
const int SPEEDOMETER = A0;
unsigned long To = 0, SM = 0;
float Tc = 0;
float S = 0;
float A = 0;
const int ACCELERATOR = A1;
const int SWITCH = A2;
float MAX_V = 261.0; //km/h
float MAX_C = 60.0;
float THRHD_C = 40.0;
int PWM = 0;
const int CURRENT = A3;
const int MOTOR = 3;
float MAX_A = 15113.830414986014785040906949407;
int MAX_PWM = 255, MIN_PWM = 0;

int x1, y1, x2, y2;
float a1 = 0, a2 = 0, a3 = 0, a1b = 0, a2b = 0, a3b = 0;


void setup() {

  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println(" D_EAZYLIFE +2348051548082");
  tft.drawCircle(80, 99, 80, ILI9341_WHITE);
  tft.fillCircle(80, 141, 80, ILI9341_BLACK);
  tft.drawCircle(240, 99, 80, ILI9341_WHITE);
  tft.fillCircle(240, 141, 80, ILI9341_BLACK);
  tft.drawCircle(160, 200, 80, ILI9341_WHITE);
  tft.fillCircle(160, 241, 80, ILI9341_BLACK);

  for (float x = -15.0; x < 120.0; x += 210.0 / 70) {
    x1 = 80 - (66 * cosd(x)); x2 = 80 - (75 * cosd(x));
    y1 = 99 - (66 * sind(x)); y2 = 99 - (75 * sind(x));
    tft.drawLine(x1, y1, x2, y2, ILI9341_GREEN);
    x1 = 240 - (66 * cosd(x)); x2 = 240 - (75 * cosd(x));
    y1 = 99 - (66 * sind(x)); y2 = 99 - (75 * sind(x));
    tft.drawLine(x1, y1, x2, y2, ILI9341_GREEN);
    x1 = 160 - (66 * cosd(x)); x2 = 160 - (75 * cosd(x));
    y1 = 200 - (66 * sind(x)); y2 = 200 - (75 * sind(x));
    tft.drawLine(x1, y1, x2, y2, ILI9341_GREEN);
  }
  for (float x = 120.0; x < 180.75; x += 210.0 / 70) {
    x1 = 80 - (66 * cosd(x)); x2 = 80 - (75 * cosd(x));
    y1 = 99 - (66 * sind(x)); y2 = 99 - (75 * sind(x));
    tft.drawLine(x1, y1, x2, y2, ILI9341_YELLOW);
    x1 = 240 - (66 * cosd(x)); x2 = 240 - (75 * cosd(x));
    y1 = 99 - (66 * sind(x)); y2 = 99 - (75 * sind(x));
    tft.drawLine(x1, y1, x2, y2, ILI9341_YELLOW);
    x1 = 160 - (66 * cosd(x)); x2 = 160 - (75 * cosd(x));
    y1 = 200 - (66 * sind(x)); y2 = 200 - (75 * sind(x));
    tft.drawLine(x1, y1, x2, y2, ILI9341_YELLOW);
  }
  for (float x = 180.75; x < 195.0; x += 210.0 / 70) {
    x1 = 80 - (66 * cosd(x)); x2 = 80 - (75 * cosd(x));
    y1 = 99 - (66 * sind(x)); y2 = 99 - (75 * sind(x));
    tft.drawLine(x1, y1, x2, y2, ILI9341_RED);
    x1 = 240 - (66 * cosd(x)); x2 = 240 - (75 * cosd(x));
    y1 = 99 - (66 * sind(x)); y2 = 99 - (75 * sind(x));
    tft.drawLine(x1, y1, x2, y2, ILI9341_RED);
    x1 = 160 - (66 * cosd(x)); x2 = 160 - (75 * cosd(x));
    y1 = 200 - (66 * sind(x)); y2 = 200 - (75 * sind(x));
    tft.drawLine(x1, y1, x2, y2, ILI9341_RED);
  }

  tft.setTextColor(ILI9341_WHITE);
  int yi = 0, yj = 0, yk = 0, num = 0;
  for (float x = -15.0; x < 120.0; x += 210.0 / 14) {
    x1 = 80 - (60 * cosd(x)); x2 = 80 - (75 * cosd(x));
    y1 = 99 - (60 * sind(x)); y2 = 99 - (75 * sind(x));
    tft.drawLine(x1, y1, x2, y2, ILI9341_GREEN);

    if (num == 0) {
      if (x <= 60) {
        tft.setCursor(x1, y1);
      }
      else {
        tft.setCursor(x1-5, y1);
      }
      tft.setTextSize(1);
      tft.println(yi);
    }

    x1 = 240 - (60 * cosd(x)); x2 = 240 - (75 * cosd(x));
    y1 = 99 - (60 * sind(x)); y2 = 99 - (75 * sind(x));
    tft.drawLine(x1, y1, x2, y2, ILI9341_GREEN);

    if (num == 0) {
      if (x <= 60) {
        tft.setCursor(x1, y1);
      }
      else {
        tft.setCursor(x1-5, y1);
      }
      tft.setTextSize(1);
      tft.println(yj);
    }

    x1 = 160 - (60 * cosd(x)); x2 = 160 - (75 * cosd(x));
    y1 = 200 - (60 * sind(x)); y2 = 200 - (75 * sind(x));
    tft.drawLine(x1, y1, x2, y2, ILI9341_GREEN);

    if (num == 0) {
      if (x <= 60) {
        tft.setCursor(x1, y1);
      }
      else {
        tft.setCursor(x1-8, y1);
      }
      tft.setTextSize(1);
      tft.println(yk);
    }

    if (num == 0) {
      num = 1;
    }
    else if (num == 1) {
      num = 0;
    }

    yi += 5;
    yj += 10;
    yk += 20;
  }

  yi = 45, yj = 90, yk = 180, num = 1;
  for (float x = 120.0; x < 180.75; x += 210.0 / 14) {
    x1 = 80 - (60 * cosd(x)); x2 = 80 - (75 * cosd(x));
    y1 = 99 - (60 * sind(x)); y2 = 99 - (75 * sind(x));
    tft.drawLine(x1, y1, x2, y2, ILI9341_YELLOW);

    if (num == 0) {
      tft.setCursor(x1-6, y1+2);
      tft.setTextSize(1);
      tft.println(yi);
    }

    x1 = 240 - (60 * cosd(x)); x2 = 240 - (75 * cosd(x));
    y1 = 99 - (60 * sind(x)); y2 = 99 - (75 * sind(x));
    tft.drawLine(x1, y1, x2, y2, ILI9341_YELLOW);

    if (num == 0) {
      tft.setCursor(x1-11, y1+2);
      tft.setTextSize(1);
      tft.println(yj);
    }

    x1 = 160 - (60 * cosd(x)); x2 = 160 - (75 * cosd(x));
    y1 = 200 - (60 * sind(x)); y2 = 200 - (75 * sind(x));
    tft.drawLine(x1, y1, x2, y2, ILI9341_YELLOW);

    if (num == 0) {
      tft.setCursor(x1-11, y1+2);
      tft.setTextSize(1);
      tft.println(yk);
    }

    if (num == 0) {
      num = 1;
    }
    else if (num == 1) {
      num = 0;
    }

    yi += 5;
    yj += 10;
    yk += 20;
  }

  yi = 65, yj = 130, yk = 260, num = 1;
  for (float x = 180.75; x < 196.0; x += 210.0 / 14) {
    x1 = 80 - (60 * cosd(x)); x2 = 80 - (75 * cosd(x));
    y1 = 99 - (60 * sind(x)); y2 = 99 - (75 * sind(x));
    tft.drawLine(x1, y1, x2, y2, ILI9341_RED);

    if (num == 0) {
      tft.setCursor(x1-11, y1+1);
      tft.setTextSize(1);
      tft.println(yi);
    }

    x1 = 240 - (60 * cosd(x)); x2 = 240 - (75 * cosd(x));
    y1 = 99 - (60 * sind(x)); y2 = 99 - (75 * sind(x));
    tft.drawLine(x1, y1, x2, y2, ILI9341_RED);

    if (num == 0) {
      tft.setCursor(x1-15, y1+2);
      tft.setTextSize(1);
      tft.println(yj);
    }

    x1 = 160 - (60 * cosd(x)); x2 = 160 - (75 * cosd(x));
    y1 = 200 - (60 * sind(x)); y2 = 200 - (75 * sind(x));
    tft.drawLine(x1, y1, x2, y2, ILI9341_RED);

    if (num == 0) {
      tft.setCursor(x1-15, y1+2);
      tft.setTextSize(1);
      tft.println(yk);
    }

    if (num == 0) {
      num = 1;
    }
    else if (num == 1) {
      num = 0;
    }

    yi += 5;
    yj += 10;
    yk += 20;
  }

  tft.setTextColor(ILI9341_RED);
  tft.setCursor(70, 109);
  tft.setTextSize(1);
  tft.println("Amps");

  tft.setTextColor(ILI9341_YELLOW);
  tft.setCursor(225, 109);
  tft.setTextSize(1);
  tft.println("Km/Hr");
  tft.setCursor(255, 106);
  tft.println("2");

  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(145, 210);
  tft.setTextSize(1);
  tft.println("Km/Hr");

  tft.fillCircle(80, 99, 3, ILI9341_RED);
  tft.fillCircle(240, 99, 3, ILI9341_YELLOW);
  tft.fillCircle(160, 200, 3, ILI9341_GREEN);


  lcd.begin(16, 4);
  // create a new character
  lcd.createChar(1, squa);

  lcd.clear();
  lcd.setCursor(2, 1);
  lcd.print("D_EAZYLIFE");
  lcd.setCursor(2, 2);
  lcd.print("07051548082");
  delay(1000);

  Serial.begin(38400);
  pinMode(SPEEDOMETER, INPUT);
  pinMode(ACCELERATOR, INPUT);
  pinMode(SWITCH, INPUT);
  pinMode(CURRENT, INPUT);
  pinMode(MOTOR, OUTPUT);
}
void loop() {
  SM = pulseIn(SPEEDOMETER, HIGH, 5000000);

  V = map_V(SM);
  A = sqrt(pow(((V - U) / ((micros() - To) / 3600000000.0)), 2));
  //  S += (pow(V, 2) - pow(U, 2)) / (2.0 * A);
  S += ((V + U) * ((micros() - To) / 3600000000.0)) / 2.0;

  U = V;
  To = micros();

  if (digitalRead(SWITCH) == HIGH) {
    if (A > map_A(analogRead(ACCELERATOR)) || map_A(analogRead(ACCELERATOR)) <= 0 || V > MAX_V || map_C(analogRead(CURRENT)) > MAX_C) {
      PWM = 0;
      analogWrite(MOTOR, PWM);
    }
    else {
      PWM = constrain(map_PWM(map_C(analogRead(CURRENT))), 0, 255);
      analogWrite(MOTOR, PWM);
    }
  }
  else {
    PWM = 0;
    analogWrite(MOTOR, PWM);
  }


  a1 = dis_C(map_C(analogRead(CURRENT)));
  a2 = dis_A(map_A(analogRead(ACCELERATOR)));
  a3 = dis_V(V);

  x2 = 80 - (45 * cosd(a1b));
  y2 = 99 - (45 * sind(a1b));
  tft.drawLine(80, 99, x2, y2, ILI9341_BLACK);

  x2 = 240 - (45 * cosd(a2b));
  y2 = 99 - (45 * sind(a2b));
  tft.drawLine(240, 99, x2, y2, ILI9341_BLACK);

  x2 = 160 - (45 * cosd(a3b));
  y2 = 200 - (45 * sind(a3b));
  tft.drawLine(160, 200, x2, y2, ILI9341_BLACK);

  tft.fillCircle(80, 99, 3, ILI9341_RED);
  tft.fillCircle(240, 99, 3, ILI9341_YELLOW);
  tft.fillCircle(160, 200, 3, ILI9341_GREEN);

  x2 = 80 - (45 * cosd(a1));
  y2 = 99 - (45 * sind(a1));
  tft.drawLine(80, 99, x2, y2, ILI9341_RED);

  x2 = 240 - (45 * cosd(a2));
  y2 = 99 - (45 * sind(a2));
  tft.drawLine(240, 99, x2, y2, ILI9341_YELLOW);

  x2 = 160 - (45 * cosd(a3));
  y2 = 200 - (45 * sind(a3));
  tft.drawLine(160, 200, x2, y2, ILI9341_GREEN);

  a1b = a1;
  a2b = a2;
  a3b = a3;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Spd="), lcd.print(V), lcd.print("Km/Hr");
  lcd.setCursor(0, 1);
  lcd.print("Acc="), lcd.print(map_A(analogRead(ACCELERATOR))), lcd.print("Km/Hr"), lcd.write(1);
  lcd.setCursor(0, 2);
  lcd.print("Dis="), lcd.print(S), lcd.print("Km");
  lcd.setCursor(0, 3);
  lcd.print("C = "), lcd.print(map_C(analogRead(CURRENT))), lcd.print(" A");
  delay(100);
}

float map_V(unsigned long MV) {
  if (MV <= 0) {
    return 0; //km/hr //R=TIRE RADIUS IN METER
  }
  else {
    return (2.0 * 3.142 * (R / 1000.0)) / (MV / 3600000000.0); //km/hr //R=TIRE RADIUS IN METER
  }
}

float map_A(float MA) {
  return map(MA, 0, 1024, 0, MAX_A); //km/hr^2   60mph=9.65606km/hr  2.3s=0.000638889h A=15,113.830414986014785040906949407 km/hr^2
}

float map_C(float MC) {
  return map(MC, 0, 1024, 0, MAX_C); //I
}

float map_PWM(float CURR) {
  return map(CURR, THRHD_C, MAX_C, MAX_PWM, MIN_PWM); //I
}

float dis_C(float DC) {
  return constrain(map(DC, 0, MAX_C, -15.0, 196.0), -15.0, 196.0); //I
}

float dis_A(float DA) {
  return constrain(map(DA, 0, MAX_A, -15.0, 196.0), -15.0, 196.0); //I
}

float dis_V(float DV) {
  return constrain(map(DV, 0, MAX_V, -15.0, 180.75), -15.0, 196.0); //I
}


float sind(float calc_sin) {
  return sin(calc_sin * 0.017453);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

float cosd(float calc_cos) {
  return cos(calc_cos * 0.017453);
}
