#include <BasicLinearAlgebra.h>
using namespace BLA;
#include <AccelStepper.h>
#include <MultiStepper.h>

AccelStepper stepper1(AccelStepper::FULL4WIRE, 2, 3, 4, 5);
AccelStepper stepper2(AccelStepper::FULL4WIRE, 6, 7, 8, 9);
AccelStepper stepper3(AccelStepper::FULL4WIRE, 10, 11, 12, 13);
AccelStepper stepper4(AccelStepper::FULL4WIRE, 17, 16, 15, 14);
AccelStepper stepper5(AccelStepper::FULL4WIRE, 21, 20, 19, 18);
AccelStepper stepper6(AccelStepper::FULL4WIRE, 25, 24, 23, 22);
MultiStepper steppers;
long positions[6];

////////////////////////////////////////////////////////////////////////////////////////////////////////

String bt_read, x, y, z, w, u, q;
float XE = 0.0, YE = 0.0, ZE = 0.0, W, U, Q;
float M1 = 0.0, M2 = 0.0, M3 = 0.0, MQ1 = 0.0, MQ2 = 0.0, MQ3 = 0.0;

////////////////////////////////////////////////////////////////////////////////////////////////////////

float Pstore[15][6];
unsigned long no = 0;
String DO = "SINGLE";
float XF, YF, ZF, WF, UF, QF;

////////////////////////////////////////////////////////////////////////////////////////////////////////

int com_pos = -1;
String nw_bt;
int x_read, y_read, z_read, w_read, u_read;
String nw_read;
////////////////////////////////////////////////////////////////////////////////////////////////////////
int REPEAT_ERROR = 0;
////////////////////////////////////////////////////////////////////////////////////////////////////////

//FORWARD_INPUT_DEG
float B4 = 10.0; //DEG1
float B5 = 30.0; //DEG2
float B6 = 30.0; //DEG3
float B7 = 15.0; //DEG4
float B8 = 12.0; //DEG5
float B9 = 20.0; //DEG6

//FORWARD_INPUT_DEG_TO_RADIAN
float C4; //DEG1->RAD1
float C5; //DEG2->RAD2
float C6; //DEG3->RAD3
float C7; //DEG4->RAD4
float C8; //DEG5->RAD5
float C9; //DEG6->RAD6


//FORWARD_INPUT_4X_MATRIX_DH
float C13 /*@1*/, D13 /*&1*/, E13 /*d1*/, F13 /*a1*/;
float C14 /*@2*/, D14 /*&2*/, E14 /*d2*/, F14 /*a2*/;
float C15 /*@3*/, D15 /*&3*/, E15 /*d3*/, F15 /*a3*/;
float C16 /*@4*/, D16 /*&4*/, E16 /*d4*/, F16 /*a4*/;
float C17 /*@5*/, D17 /*&5*/, E17 /*d5*/, F17 /*a5*/;
float C18 /*@6*/, D18 /*&6*/, E18 /*d6*/, F18 /*a6*/;


//WORK_FRAME
float H13; //X
float H14; //Y
float H15; //Z
float H16; //yaw(x)
float H17; //pitch(y)
float H18; //roll(z)

//TOOL_FRAME
float J13; //X
float J14; //Y
float J15; //Z
float J16; //yaw(x)
float J17; //pitch(y)
float J18; //roll(z)
//
////FORWARD_WORK_FRAME_4X4_MATRIX
//BLA::Matrix<4, 4>FWF;
//
////FORWARD_TOOL_FRAME_4X4_MATRIX
//BLA::Matrix<4, 4>FTF;
//
////FORWARD_J1_4X4_MATRIX
//BLA::Matrix<4, 4>FJ1;
//
////FORWARD_J2_4X4_MATRIX
//BLA::Matrix<4, 4>FJ2;
//
////FORWARD_J3_4X4_MATRIX
//BLA::Matrix<4, 4>FJ3;
//
////FORWARD_J4_4X4_MATRIX
//BLA::Matrix<4, 4>FJ4;
//
////FORWARD_J5_4X4_MATRIX
//BLA::Matrix<4, 4>FJ5;
//
////FORWARD_J6_4X4_MATRIX
//BLA::Matrix<4, 4>FJ6;
//
////FORWARD_R_0_1_4X4_MATRIX
//BLA::Matrix<4, 4>FR01;
//
////FORWARD_R_0_2_4X4_MATRIX
//BLA::Matrix<4, 4>FR02;
//
////FORWARD_R_0_3_4X4_MATRIX
//BLA::Matrix<4, 4>FR03;
//
////FORWARD_R_0_4_4X4_MATRIX
//BLA::Matrix<4, 4>FR04;
//
////FORWARD_R_0_5_4X4_MATRIX
//BLA::Matrix<4, 4>FR05;
//
////FORWARD_R_0_6_4X4_MATRIX
//BLA::Matrix<4, 4>FR06;
//
////FORWARD_R_0_T_4X4_MATRIX
//BLA::Matrix<4, 4>FR0T;

//FORWARD_OUT_PUT
float H4; //X
float H5; //Y
float H6; //Z
float I7; //y(rad)
float I8; //p(rad)
float I9; //r(rad)
float H7; //y(deg)
float H8; //p(deg)
float H9; //r(deg)

//REVERSE_IN_PUT
float O4; //X
float O5; //Y
float O6; //Z
float O7; //y(deg)
float O8; //p(deg)
float O9; //r(deg)
//
////REVERSE_WORK_FRAME_4X4_MATRIX
//BLA::Matrix<4, 4>RWF;
//
////REVERSE_R_0_T_4X4_MATRIX
//BLA::Matrix<4, 4>RR0T;
//
////REVERSE_R_0_T_WORKFRAME_OFFSET_4X4_MATRIX
//BLA::Matrix<4, 4>RR0TWF;
//
////REVERSE_TOOL_FRAME_4X4_MATRIX
//BLA::Matrix<4, 4>RTF;
//
////REVERSE_INVERT_TOOL_FRAME_4X4_MATRIX
//BLA::Matrix<4, 4>RITF;
//
////REVERSE_R_0_6_4X4_MATRIX
//BLA::Matrix<4, 4>RR06;
//
////REVERSE_REMOVE_R_0_6_4X4_MATRIX
//BLA::Matrix<4, 4>RRR06;
//
////REVERSE_R_0_5_4X4_MATRIX
//BLA::Matrix<4, 4>RR05;

//WRIST_CONF_QUADRANT
float V9;

//J1_ANG
float O13 /*RAD*/, P13 /*DEG*/;

//FWD_MID
float O16 /*FWD*/, P16 /*MID*/; //PX
float O17 /*FWD*/, P17 /*MID*/; //PY
float O18 /*FWD*/, P18 /*MID*/; //PX-A1
float O19 /*FWD*/, P19 /*MID*/; //PA2H
float O20 /*FWD*/, P20 /*MID*/; //PA3H
float O21 /*FWD*/, P21 /*MID*/; //@A
float O22 /*FWD*/, P22 /*MID*/; //@B
float O23 /*FWD*/, P23 /*MID*/; //@C
float O24 /*FWD*/, P24 /*MID*/; //@D
float O25 /*FWD*/, P25 /*MID*/; //@E
float O26 /*FWD*/, P26 /*MID*/; //J2_ANG
float O27 /*FWD*/, P27 /*MID*/; //J3_ANG

//REVERSE_OUT_PUT1
float Q4; //J1
float Q5; //J2
float Q6; //J3
//
////REVERSE_J1_4X4_MATRIX
//BLA::Matrix<4, 4>RJ1;
//
////REVERSE_J2_4X4_MATRIX
//BLA::Matrix<4, 4>RJ2;
//
////REVERSE_J3_4X4_MATRIX
//BLA::Matrix<4, 4>RJ3;
//
////REVERSE_R_0_1_4X4_MATRIX
//BLA::Matrix<4, 4>RR01;
//
////REVERSE_R_0_2_4X4_MATRIX
//BLA::Matrix<4, 4>RR02;
//
////REVERSE_R_0_3_4X4_MATRIX
//BLA::Matrix<4, 4>RR03;
//
////REVERSE_R_0_3_TRANSPOSED_3X3_MATRIX
//BLA::Matrix<3, 3>RR03T;
//
////REVERSE_R_3_6_3X3_MATRIX
//BLA::Matrix<3, 3>RR36;

//REVERSE_OUT_PUT2
float Q7, R7, S7; //J4
float Q8, R8, S8; //J5
float Q9, R9, S9; //J6





void setup() {

  //FORWARD_WORK_FRAME_4X4_MATRIX
  BLA::Matrix<4, 4>FWF;

  //FORWARD_TOOL_FRAME_4X4_MATRIX
  BLA::Matrix<4, 4>FTF;

  //FORWARD_J1_4X4_MATRIX
  BLA::Matrix<4, 4>FJ1;

  //FORWARD_J2_4X4_MATRIX
  BLA::Matrix<4, 4>FJ2;

  //FORWARD_J3_4X4_MATRIX
  BLA::Matrix<4, 4>FJ3;

  //FORWARD_J4_4X4_MATRIX
  BLA::Matrix<4, 4>FJ4;

  //FORWARD_J5_4X4_MATRIX
  BLA::Matrix<4, 4>FJ5;

  //FORWARD_J6_4X4_MATRIX
  BLA::Matrix<4, 4>FJ6;

  //FORWARD_R_0_1_4X4_MATRIX
  BLA::Matrix<4, 4>FR01;

  //FORWARD_R_0_2_4X4_MATRIX
  BLA::Matrix<4, 4>FR02;

  //FORWARD_R_0_3_4X4_MATRIX
  BLA::Matrix<4, 4>FR03;

  //FORWARD_R_0_4_4X4_MATRIX
  BLA::Matrix<4, 4>FR04;

  //FORWARD_R_0_5_4X4_MATRIX
  BLA::Matrix<4, 4>FR05;

  //FORWARD_R_0_6_4X4_MATRIX
  BLA::Matrix<4, 4>FR06;

  //FORWARD_R_0_T_4X4_MATRIX
  BLA::Matrix<4, 4>FR0T;

  //REVERSE_WORK_FRAME_4X4_MATRIX
  BLA::Matrix<4, 4>RWF;

  //REVERSE_R_0_T_4X4_MATRIX
  BLA::Matrix<4, 4>RR0T;

  //REVERSE_R_0_T_WORKFRAME_OFFSET_4X4_MATRIX
  BLA::Matrix<4, 4>RR0TWF;

  //REVERSE_TOOL_FRAME_4X4_MATRIX
  BLA::Matrix<4, 4>RTF;

  //REVERSE_INVERT_TOOL_FRAME_4X4_MATRIX
  BLA::Matrix<4, 4>RITF;

  //REVERSE_R_0_6_4X4_MATRIX
  BLA::Matrix<4, 4>RR06;

  //REVERSE_REMOVE_R_0_6_4X4_MATRIX
  BLA::Matrix<4, 4>RRR06;

  //REVERSE_R_0_5_4X4_MATRIX
  BLA::Matrix<4, 4>RR05;

  //REVERSE_J1_4X4_MATRIX
  BLA::Matrix<4, 4>RJ1;

  //REVERSE_J2_4X4_MATRIX
  BLA::Matrix<4, 4>RJ2;

  //REVERSE_J3_4X4_MATRIX
  BLA::Matrix<4, 4>RJ3;

  //REVERSE_R_0_1_4X4_MATRIX
  BLA::Matrix<4, 4>RR01;

  //REVERSE_R_0_2_4X4_MATRIX
  BLA::Matrix<4, 4>RR02;

  //REVERSE_R_0_3_4X4_MATRIX
  BLA::Matrix<4, 4>RR03;

  //REVERSE_R_0_3_TRANSPOSED_3X3_MATRIX
  BLA::Matrix<3, 3>RR03T;

  //REVERSE_R_3_6_3X3_MATRIX
  BLA::Matrix<3, 3>RR36;


  //////////////////////////


  //FORWARD_WORK_FRAME_4X4_MATRIX
  FWF.Fill(0);

  //FORWARD_TOOL_FRAME_4X4_MATRIX
  FTF.Fill(0);

  //FORWARD_J1_4X4_MATRIX
  FJ1.Fill(0);

  //FORWARD_J2_4X4_MATRIX
  FJ2.Fill(0);

  //FORWARD_J3_4X4_MATRIX
  FJ3.Fill(0);

  //FORWARD_J4_4X4_MATRIX
  FJ4.Fill(0);

  //FORWARD_J5_4X4_MATRIX
  FJ5.Fill(0);

  //FORWARD_J6_4X4_MATRIX
  FJ6.Fill(0);

  //FORWARD_R_0_1_4X4_MATRIX
  FR01.Fill(0);

  //FORWARD_R_0_2_4X4_MATRIX
  FR02.Fill(0);

  //FORWARD_R_0_3_4X4_MATRIX
  FR03.Fill(0);

  //FORWARD_R_0_4_4X4_MATRIX
  FR04.Fill(0);

  //FORWARD_R_0_5_4X4_MATRIX
  FR05.Fill(0);

  //FORWARD_R_0_6_4X4_MATRIX
  FR06.Fill(0);

  //FORWARD_R_0_T_4X4_MATRIX
  FR0T.Fill(0);

  //REVERSE_WORK_FRAME_4X4_MATRIX
  RWF.Fill(0);

  //REVERSE_R_0_T_4X4_MATRIX
  RR0T.Fill(0);

  //REVERSE_R_0_T_WORKFRAME_OFFSET_4X4_MATRIX
  RR0TWF.Fill(0);

  //REVERSE_TOOL_FRAME_4X4_MATRIX
  RTF.Fill(0);

  //REVERSE_INVERT_TOOL_FRAME_4X4_MATRIX
  RITF.Fill(0);

  //REVERSE_R_0_6_4X4_MATRIX
  RR06.Fill(0);

  //REVERSE_REMOVE_R_0_6_4X4_MATRIX
  RRR06.Fill(0);

  //REVERSE_R_0_5_4X4_MATRIX
  RR05.Fill(0);

  //REVERSE_J1_4X4_MATRIX
  RJ1.Fill(0);

  //REVERSE_J2_4X4_MATRIX
  RJ2.Fill(0);

  //REVERSE_J3_4X4_MATRIX
  RJ3.Fill(0);

  //REVERSE_R_0_1_4X4_MATRIX
  RR01.Fill(0);

  //REVERSE_R_0_2_4X4_MATRIX
  RR02.Fill(0);

  //REVERSE_R_0_3_4X4_MATRIX
  RR03.Fill(0);

  //REVERSE_R_0_3_TRANSPOSED_3X3_MATRIX
  RR03T.Fill(0);

  //REVERSE_R_3_6_3X3_MATRIX
  RR36.Fill(0);




  //////////////////////

  Serial.begin(38400);
  FORWARD_CALCULATION();
  REVERSE_IN_PUT();
  INVERSE_CALCULATION();
  Serial.println("");
  Serial.println("FOWARD OUTPUT = ");
  //FORWARD_OUT_PUT
  Serial.println(H4);
  Serial.println(H5);
  Serial.println(H6);
  Serial.println(H7);
  Serial.println(H8);
  Serial.println(H9);
  Serial.println("");

  Serial.println("INVERSE OUTPUT = ");
  //INVERSE_OUT_PUT
  Serial.println(Q4);
  Serial.println(Q5);
  Serial.println(Q6);
  Serial.println(Q7);
  Serial.println(Q8);
  Serial.println(Q9);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////

  stepper1.setMaxSpeed(300);
  stepper2.setMaxSpeed(300);
  stepper3.setMaxSpeed(300);
  stepper4.setMaxSpeed(300);
  stepper5.setMaxSpeed(300);
  stepper6.setMaxSpeed(300);
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);
  steppers.addStepper(stepper3);
  steppers.addStepper(stepper4);
  steppers.addStepper(stepper5);
  steppers.addStepper(stepper6);
  FORWARD_INPUT_X4_MATRIX_DH();
  XE = 0.0;
  YE = 0.0;
  ZE = E13 + F14 + D16 + D18;
  W = 0;
  U = 0;
  Q = 0;
  XF = XE, YF = YE, ZF = ZE, WF = W, UF = U, QF = Q;
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.println("SINGLE MOVE");
}

void loop() {
  if (Serial.available()) {
    bt_read = Serial.readString();

    if (bt_read.indexOf("STORE") > -1 || bt_read.indexOf("CLEAR") > -1) {
      DO = "STORE";
      no = 0;
      Serial.println("");
      Serial.println("STORE MOVE");
    }
    else if (bt_read.indexOf("LOOP") > -1) {
      DO = "LOOP";
      Serial.println("");
      Serial.println("LOOP MOVE");
    }
    else if (bt_read.indexOf("SING") > -1) {
      DO = "SINGLE";
      no = 0;
      Serial.println("");
      Serial.println("SINGLE MOVE");
    }

    else if (bt_read.indexOf("HOME") > -1) {
      XE = 0.0;
      YE = 0.0;
      ZE = E13 + F14 + D16 + D18;
      W = 0;
      U = 0;
      Q = 0;
      if (XF == XE && YF == YE && ZF == ZE && WF == W && UF == U && QF == Q) {
        Serial.println("");
        Serial.println("REPEATED LOCATION :");
        Serial.println("HOME");
        XYZWUQ();
      }
      else {
        Serial.println("");
        Serial.println("HOME");
      }
    }

    else if (bt_read.indexOf("(") > -1 && bt_read.indexOf(")") > -1) {
      x = bt_read.substring (bt_read.indexOf("(") + 1, bt_read.indexOf(","));
      x_read = bt_read.indexOf(",");
      y = bt_read.substring (x_read + 1, bt_read.indexOf(",", x_read + 1));
      y_read = bt_read.indexOf(",", x_read + 1);
      z = bt_read.substring (y_read + 1, bt_read.indexOf(",", y_read + 1));
      z_read = bt_read.indexOf(",", y_read + 1);
      w = bt_read.substring (z_read + 1, bt_read.indexOf(",", z_read + 1));
      w_read = bt_read.indexOf(",", z_read + 1);
      u = bt_read.substring (w_read + 1, bt_read.indexOf(",", w_read + 1));
      u_read = bt_read.indexOf(",", w_read + 1);
      q = bt_read.substring (u_read + 1, bt_read.indexOf(")"));

      XE = x.toFloat();
      YE = y.toFloat();
      ZE = z.toFloat();
      W = w.toFloat();
      U = u.toFloat();
      Q = q.toFloat();
      if (XF == XE && YF == YE && ZF == ZE && WF == W && UF == U && QF == Q) {
        Serial.println("");
        Serial.println("REPEATED LOCATION :");
        XYZWUQ();
      }
      if (DO == "STORE" && bt_read.indexOf(")(") > -1) {
        nw_bt = bt_read.substring (bt_read.indexOf("("), (bt_read.length() - 1));
        com_pos = nw_bt.indexOf(")(");
      }
    }
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////

  if (DO == "SINGLE" && (XF != XE || YF != YE || ZF != ZE || WF != W || UF != U || QF != Q)) {
    REPEAT_ERROR = 0;
    Calc_Move();
  }

  if (DO == "STORE" && (XF != XE || YF != YE || ZF != ZE || WF != W || UF != U || QF != Q)) {
    REPEAT_ERROR = 0;
    Calc_Move();
    Pstore[no][0] = XE, Pstore[no][1] = YE, Pstore[no][2] = ZE, Pstore[no][3] = W, Pstore[no][4] = U, Pstore[no][5] = Q;
    no++;

    ///////////////////////////////////////////////////////////////

    while (com_pos > -1) {
      nw_read = nw_bt.substring (com_pos + 1, nw_bt.indexOf(")(", com_pos + 1));
      nw_read += ")";
      com_pos = nw_bt.indexOf(")(", com_pos + 1);

      x = nw_read.substring (nw_read.indexOf("(") + 1, nw_read.indexOf(","));
      x_read = nw_read.indexOf(",");
      y = nw_read.substring (x_read + 1, nw_read.indexOf(",", x_read + 1));
      y_read = nw_read.indexOf(",", x_read + 1);
      z = nw_read.substring (y_read + 1, nw_read.indexOf(",", y_read + 1));
      z_read = nw_read.indexOf(",", y_read + 1);
      w = nw_read.substring (z_read + 1, nw_read.indexOf(",", z_read + 1));
      w_read = nw_read.indexOf(",", z_read + 1);
      u = nw_read.substring (w_read + 1, nw_read.indexOf(",", w_read + 1));
      u_read = nw_read.indexOf(",", w_read + 1);
      q = nw_read.substring (u_read + 1, nw_read.indexOf(")"));

      XE = x.toFloat();
      YE = y.toFloat();
      ZE = z.toFloat();
      W = w.toFloat();
      U = u.toFloat();
      Q = q.toFloat();

      Calc_Move();
      Pstore[no][0] = XE, Pstore[no][1] = YE, Pstore[no][2] = ZE, Pstore[no][3] = W, Pstore[no][4] = U, Pstore[no][5] = Q;
      no++;
    }
  }

  if (DO == "LOOP") {
    for (int i = 0; i < no; i++) {
      XE = Pstore[i][0];
      YE = Pstore[i][1];
      ZE = Pstore[i][2];
      W = Pstore[i][3];
      U = Pstore[i][4];
      Q = Pstore[i][5];
      Calc_Move();
    }
  }
}

void Calc_Move() {
  Serial.println("");
  Serial.println("CALCULATING.......................................................");
  DOF_REVERSE_IN_PUT();
  INVERSE_CALCULATION();
  if ((Q4 < -360 && Q4 > 360) || (Q5 < -360 && Q5 > 360) || (Q6 < -360 && Q6 > 360) || (Q7 < -360 && Q7 > 360) || (Q8 < -360 && Q8 > 360) || (Q9 < -360 && Q9 > 360)) {
    Serial.println("CALC..FAILED.......................................................");

    Serial.println(""), Serial.println("LOCATION ERROR! ON :");
    XYZWUQ();
    XE = XF, YE = YF, ZE = ZF, W = WF;
    Serial.println("");
    Serial.println("WILL REMAIN AT");
    Serial.println("PREVIOUS LOCATION :");
    XYZWUQ();
  }
  else {
    Serial.println("CALC..PASSED.......................................................");
    XYZWUQ();
    Serial.println("");
    Serial.print("Q4 = "), Serial.print(Q4);
    Serial.print(",  Q5 = "), Serial.print(Q5);
    Serial.print(",  Q6 = "), Serial.print(Q6);
    Serial.print(",  Q7 = "), Serial.print(Q7);
    Serial.print(",  Q8 = "), Serial.print(Q8);
    Serial.print(",  Q9 = "), Serial.println(Q9);
    positions[0] = map(Q4, -360.0, 360.0, -360, 360);
    positions[1] = map(Q5, -360.0, 360.0, -360, 360);
    positions[2] = map(Q6, -360.0, 360.0, -360, 360);
    positions[3] = map(Q7, -360.0, 360.0, -360, 360);
    positions[4] = map(Q8, -360.0, 360.0, -360, 360);
    positions[5] = map(Q9, -360.0, 360.0, -360, 360);
    Serial.println("MOVING.......................................................");
    Serial.println("");
    Serial.print("M1 = "), Serial.print(positions[0]);
    Serial.print(",  M2 = "), Serial.print(positions[1]);
    Serial.print(",  M3 = "), Serial.print(positions[2]);
    Serial.print(",  MQ1 = "), Serial.print(positions[3]);
    Serial.print(",  MQ2 = "), Serial.print(positions[4]);
    Serial.print(",  MQ3 = "), Serial.println(positions[5]);
    steppers.moveTo(positions);
    steppers.runSpeedToPosition(); // Blocks until all are in position
    delay(10);
    XF = XE, YF = YE, ZF = ZE, WF = W, UF = U, QF = Q;

    Serial.println("MOVED TO POSITION.......................................................");
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
void XYZWUQ() {
  Serial.print("X = "), Serial.print(XE);
  Serial.print(",  Y = "), Serial.print(YE);
  Serial.print(",  Z = "), Serial.print(ZE);
  Serial.print(",  W = "), Serial.print(W);
  Serial.print(",  U = "), Serial.print(U);
  Serial.print(",  Q = "), Serial.println(Q);
  Serial.println(""), Serial.print("COPY ===>> ("), Serial.print(XE), Serial.print(","), Serial.print(YE), Serial.print(","), Serial.print(ZE), Serial.print(","), Serial.print(W), Serial.print(","), Serial.print(U), Serial.print(","), Serial.print(Q), Serial.println(")");
}

void DOF_REVERSE_IN_PUT() {
  O4 = XE; //X
  O5 = YE; //Y
  O6 = ZE; //Z
  O7 = W; //y(deg)
  O8 = U; //p(deg)
  O9 = Q; //r(deg)
}

void FORWARD_INPUT_DEG_TO_RADIAN() {
  C4 = rad(B4); //@1->r1
  C5 = rad(B5); //@2->r2
  C6 = rad((B6 - 90.0)); //@3->r3
  C7 = rad(B7); //@4->r4
  C8 = rad(B8); //@5->r5
  C9 = rad((B9 + 180.0)); //@6->r6
}

void FORWARD_INPUT_X4_MATRIX_DH() {
  C13 = C4, D13 = rad(-90.0), E13 = 169.77, F13 = 0.0;
  C14 = C5, D14 = rad(0.0), E14 = 0, F14 = 305;
  C15 = C6, D15 = rad(90.0), E15 = 0, F15 = 0;
  C16 = C7, D16 = rad(-90.0), E16 = -222.63, F16 = 0;
  C17 = C8, D17 = rad(90.0), E17 = 0, F17 = 0;
  C18 = C9, D18 = rad(0.0), E18 = -36.25, F18 = 0;
}

void FORWARD_WORK_FRAME_4X4_MATRIX() {
  FWF(0, 0) = cos(rad(H18)) * cos(rad(H17)), FWF(0, 1) = -sin(rad(H18)) * cos(rad(H16)) + cos(rad(H18)) * sin(rad(H17)) * sin(rad(H16)), FWF(0, 2) = sin(rad(H18)) * sin(rad(H16)) + cos(rad(H18)) * sin(rad(H17)) * cos(rad(H16)), FWF(0, 3) = H13;
  FWF(1, 0) = sin(rad(H18)) * cos(rad(H17)), FWF(1, 1) = cos(rad(H18)) * cos(rad(H16)) + sin(rad(H18)) * sin(rad(H17)) * sin(rad(H16)), FWF(1, 2) = -cos(rad(H18)) * sin(rad(H16)) + sin(rad(H18)) * sin(rad(H17)) * cos(rad(H16)), FWF(1, 3) = H14;
  FWF(2, 0) = -sin(rad(H18)), FWF(2, 1) = cos(rad(H17)) * sin(rad(H16)), FWF(2, 2) = cos(rad(H17)) * cos(rad(H16)), FWF(2, 3) = H15;
  FWF(3, 0) = 0, FWF(3, 1) = 0, FWF(3, 2) = 0, FWF(3, 3) = 1;
}

void FORWARD_TOOL_FRAME_4X4_MATRIX() {
  FTF(0, 0) = cos(rad(J18)) * cos(rad(J17)), FTF(0, 1) = -sin(rad(J18)) * cos(rad(J16)) + cos(rad(J18)) * sin(rad(J17)) * sin(rad(J16)), FTF(0, 2) = sin(rad(J18)) * sin(rad(J16)) + cos(rad(J18)) * sin(rad(J17)) * cos(rad(J16)), FTF(0, 3) = J13;
  FTF(1, 0) = sin(rad(J18)) * cos(rad(J17)), FTF(1, 1) = cos(rad(J18)) * cos(rad(J16)) + sin(rad(J18)) * sin(rad(J17)) * sin(rad(J16)), FTF(1, 2) = -cos(rad(J18)) * sin(rad(J16)) + sin(rad(J18)) * sin(rad(J17)) * cos(rad(J16)), FTF(1, 3) = J14;
  FTF(2, 0) = -sin(rad(J18)), FTF(2, 1) = cos(rad(J17)) * sin(rad(J16)), FTF(2, 2) = cos(rad(J17)) * cos(rad(J16)), FTF(2, 3) = J15;
  FTF(3, 0) = 0, FTF(3, 1) = 0, FTF(3, 2) = 0, FTF(3, 3) = 1;
}

void FORWARD_J1_4X4_MATRIX() {
  FJ1(0, 0) = cos(C13), FJ1(0, 1) = -sin(C13) * cos(D13), FJ1(0, 2) = sin(C13) * sin(D13), FJ1(0, 3) = F13 * cos(C13);
  FJ1(1, 0) = sin(C13), FJ1(1, 1) = cos(C13) * cos(D13), FJ1(1, 2) = -cos(C13) * sin(D13), FJ1(1, 3) = F13 * sin(C13);
  FJ1(2, 0) = 0, FJ1(2, 1) = sin(D13), FJ1(2, 2) = cos(D13), FJ1(2, 3) = E13;
  FJ1(3, 0) = 0, FJ1(3, 1) = 0, FJ1(3, 2) = 0, FJ1(3, 3) = 1;
}

void FORWARD_J2_4X4_MATRIX() {
  FJ2(0, 0) = cos(C14), FJ2(0, 1) = -sin(C14) * cos(D14), FJ2(0, 2) = sin(C14) * sin(D14), FJ2(0, 3) = F14 * cos(C14);
  FJ2(1, 0) = sin(C14), FJ2(1, 1) = cos(C14) * cos(D14), FJ2(1, 2) = -cos(C14) * sin(D14), FJ2(1, 3) = F14 * sin(C14);
  FJ2(2, 0) = 0, FJ2(2, 1) = sin(D14), FJ2(2, 2) = cos(D14), FJ2(2, 3) = E14;
  FJ2(3, 0) = 0, FJ2(3, 1) = 0, FJ2(3, 2) = 0, FJ2(3, 3) = 1;
}

void FORWARD_J3_4X4_MATRIX() {
  FJ3(0, 0) = cos(C15), FJ3(0, 1) = -sin(C15) * cos(D15), FJ3(0, 2) = sin(C15) * sin(D15), FJ3(0, 3) = F15 * cos(C15);
  FJ3(1, 0) = sin(C15), FJ3(1, 1) = cos(C15) * cos(D15), FJ3(1, 2) = -cos(C15) * sin(D15), FJ3(1, 3) = F15 * sin(C15);
  FJ3(2, 0) = 0, FJ3(2, 1) = sin(D15), FJ3(2, 2) = cos(D15), FJ3(2, 3) = E15;
  FJ3(3, 0) = 0, FJ3(3, 1) = 0, FJ3(3, 2) = 0, FJ3(3, 3) = 1;
}

void FORWARD_J4_4X4_MATRIX() {
  FJ4(0, 0) = cos(C16), FJ4(0, 1) = -sin(C16) * cos(D16), FJ4(0, 2) = sin(C16) * sin(D16), FJ4(0, 3) = F16 * cos(C16);
  FJ4(1, 0) = sin(C16), FJ4(1, 1) = cos(C16) * cos(D16), FJ4(1, 2) = -cos(C16) * sin(D16), FJ4(1, 3) = F16 * sin(C16);
  FJ4(2, 0) = 0, FJ4(2, 1) = sin(D16), FJ4(2, 2) = cos(D16), FJ4(2, 3) = E16;
  FJ4(3, 0) = 0, FJ4(3, 1) = 0, FJ4(3, 2) = 0, FJ4(3, 3) = 1;
}

void FORWARD_J5_4X4_MATRIX() {
  FJ5(0, 0) = cos(C17), FJ5(0, 1) = -sin(C17) * cos(D17), FJ5(0, 2) = sin(C17) * sin(D17), FJ5(0, 3) = F17 * cos(C17);
  FJ5(1, 0) = sin(C17), FJ5(1, 1) = cos(C17) * cos(D17), FJ5(1, 2) = -cos(C17) * sin(D17), FJ5(1, 3) = F17 * sin(C17);
  FJ5(2, 0) = 0, FJ5(2, 1) = sin(D17), FJ5(2, 2) = cos(D17), FJ5(2, 3) = E17;
  FJ5(3, 0) = 0, FJ5(3, 1) = 0, FJ5(3, 2) = 0, FJ5(3, 3) = 1;
}

void FORWARD_J6_4X4_MATRIX() {
  FJ6(0, 0) = cos(C18), FJ6(0, 1) = -sin(C18) * cos(D18), FJ6(0, 2) = sin(C18) * sin(D18), FJ6(0, 3) = F18 * cos(C18);
  FJ6(1, 0) = sin(C18), FJ6(1, 1) = cos(C18) * cos(D18), FJ6(1, 2) = -cos(C18) * sin(D18), FJ6(1, 3) = F18 * sin(C18);
  FJ6(2, 0) = 0, FJ6(2, 1) = sin(D18), FJ6(2, 2) = cos(D18), FJ6(2, 3) = E18;
  FJ6(3, 0) = 0, FJ6(3, 1) = 0, FJ6(3, 2) = 0, FJ6(3, 3) = 1;
}

void FORWARD_R_0_1_4X4_MATRIX() {
  Multiply(FWF, FJ1, FR01);
}

void FORWARD_R_0_2_4X4_MATRIX() {
  Multiply(FR01, FJ2, FR02);
}

void FORWARD_R_0_3_4X4_MATRIX() {
  Multiply(FR02, FJ3, FR03);
}

void FORWARD_R_0_4_4X4_MATRIX() {
  Multiply(FR03, FJ4, FR04);
}

void FORWARD_R_0_5_4X4_MATRIX() {
  Multiply(FR04, FJ5, FR05);
}

void FORWARD_R_0_6_4X4_MATRIX() {
  Multiply(FR05, FJ6, FR06);
}

void FORWARD_R_0_T_4X4_MATRIX() {
  Multiply(FR06, FTF, FR0T);
}

void FORWARD_OUT_PUT() {
  H4 = FR0T(0, 3); //X
  H5 = FR0T(1, 3); //Y
  H6 = FR0T(2, 3); //Z
  I8 = atan2(sqrt(pow(FR0T(0, 2), 2) + pow(FR0T(1, 2), 2)), -FR0T(2, 2));
  I7 = atan2((FR0T(2, 0) / I8), (FR0T(2, 1) / I8));
  I9 = atan2((FR0T(0, 2) / I8), (FR0T(1, 2) / I8));
  H7 = deg(I7); //y
  H8 = deg(I8); //p
  H9 = deg(I9); //r
}

void FORWARD_CALCULATION() {
  FORWARD_INPUT_DEG_TO_RADIAN();
  FORWARD_INPUT_X4_MATRIX_DH();
  FORWARD_WORK_FRAME_4X4_MATRIX();
  FORWARD_TOOL_FRAME_4X4_MATRIX();
  FORWARD_J1_4X4_MATRIX();
  FORWARD_J2_4X4_MATRIX();
  FORWARD_J3_4X4_MATRIX();
  FORWARD_J4_4X4_MATRIX();
  FORWARD_J5_4X4_MATRIX();
  FORWARD_J6_4X4_MATRIX();
  FORWARD_R_0_1_4X4_MATRIX();
  FORWARD_R_0_2_4X4_MATRIX();
  FORWARD_R_0_3_4X4_MATRIX();
  FORWARD_R_0_4_4X4_MATRIX();
  FORWARD_R_0_5_4X4_MATRIX();
  FORWARD_R_0_6_4X4_MATRIX();
  FORWARD_R_0_T_4X4_MATRIX();
  FORWARD_OUT_PUT();
}

void REVERSE_IN_PUT() {
  O4 = H4; //X
  O5 = H5; //Y
  O6 = H6; //Z
  O7 = H7; //y(deg)
  O8 = H8; //p(deg)
  O9 = H9; //r(deg)
}

void REVERSE_WORK_FRAME_4X4_MATRIX() {
  RWF(0, 0) = cos(rad(H18)) * cos(rad(H17)), RWF(0, 1) = -sin(rad(H18)) * cos(rad(H16)) + cos(rad(H18)) * sin(rad(H17)) * sin(rad(H16)), RWF(0, 2) = sin(rad(H18)) * sin(rad(H16)) + cos(rad(H18)) * sin(rad(H17)) * cos(rad(H16)), RWF(0, 3) = H13;
  RWF(1, 0) = sin(rad(H18)) * cos(rad(H17)), RWF(1, 1) = cos(rad(H18)) * cos(rad(H16)) + sin(rad(H18)) * sin(rad(H17)) * sin(rad(H16)), RWF(1, 2) = -cos(rad(H18)) * sin(rad(H16)) + sin(rad(H18)) * sin(rad(H17)) * cos(rad(H16)), RWF(1, 3) = H14;
  RWF(2, 0) = -sin(rad(H18)), RWF(2, 1) = cos(rad(H17)) * sin(rad(H16)), RWF(2, 2) = cos(rad(H17)) * cos(rad(H16)), RWF(2, 3) = H15;
  RWF(3, 0) = 0, RWF(3, 1) = 0, RWF(3, 2) = 0, RWF(3, 3) = 1;
}

void REVERSE_TOOL_FRAME_4X4_MATRIX() {
  RTF(0, 0) = cos(rad(J18)) * cos(rad(J17)), RTF(0, 1) = -sin(rad(J18)) * cos(rad(J16)) + cos(rad(J18)) * sin(rad(J17)) * sin(rad(J16)), RTF(0, 2) = sin(rad(J18)) * sin(rad(J16)) + cos(rad(J18)) * sin(rad(J17)) * cos(rad(J16)), RTF(0, 3) = J13;
  RTF(1, 0) = sin(rad(J18)) * cos(rad(J17)), RTF(1, 1) = cos(rad(J18)) * cos(rad(J16)) + sin(rad(J18)) * sin(rad(J17)) * sin(rad(J16)), RTF(1, 2) = -cos(rad(J18)) * sin(rad(J16)) + sin(rad(J18)) * sin(rad(J17)) * cos(rad(J16)), RTF(1, 3) = J14;
  RTF(2, 0) = -sin(rad(J18)), RTF(2, 1) = cos(rad(J17)) * sin(rad(J16)), RTF(2, 2) = cos(rad(J17)) * cos(rad(J16)), RTF(2, 3) = J15;
  RTF(3, 0) = 0, RTF(3, 1) = 0, RTF(3, 2) = 0, RTF(3, 3) = 1;
}

void REVERSE_INVERT_TOOL_FRAME_4X4_MATRIX() {
  RITF(0, 0) = RTF(0, 0), RITF(0, 1) = RTF(1, 0), RITF(0, 2) = RTF(2, 0), RITF(0, 3) = (RITF(0, 0) * RTF(0, 3)) + (RITF(0, 1) * RTF(1, 3)) + (RITF(0, 2) * RTF(2, 3));
  RITF(1, 0) = RTF(0, 1), RITF(1, 1) = RTF(1, 1), RITF(1, 2) = RTF(2, 1), RITF(1, 3) = (RITF(1, 0) * RTF(0, 3)) + (RITF(1, 1) * RTF(1, 3)) + (RITF(1, 2) * RTF(2, 3));
  RITF(2, 0) = RTF(0, 2), RITF(2, 1) = RTF(1, 2), RITF(2, 2) = RTF(2, 2), RITF(2, 3) = (RITF(2, 0) * RTF(0, 3)) + (RITF(2, 1) * RTF(1, 3)) + (RITF(2, 2) * RTF(2, 3));
  RITF(3, 0) = 0, RITF(3, 1) = 0, RITF(3, 2) = 0, RITF(3, 3) = 1;
}

void REVERSE_R_0_T_4X4_MATRIX() {
  RR0T(0, 0) = cos(rad(O7)) * cos(rad(O9)) - cos(rad(O8)) * sin(rad(O7)) * sin(rad(O9)), RR0T(0, 1) = cos(rad(O9)) * sin(rad(O7)) + cos(rad(O7)) * cos(rad(O8)) * sin(rad(O9)), RR0T(0, 2) = sin(rad(O8)) * sin(rad(O9)), RR0T(0, 3) = O4;
  RR0T(1, 0) = cos(rad(O8)) * cos(rad(O9)) * sin(rad(O7)) + cos(rad(O7)) * sin(rad(O9)), RR0T(1, 1) = cos(rad(O7)) * cos(rad(O8)) * cos(rad(O9)) - sin(rad(O7)) * sin(rad(O9)), RR0T(1, 2) = cos(rad(O9)) * sin(rad(O8)), RR0T(1, 3) = O5;
  RR0T(2, 0) = sin(rad(O7)) * sin(rad(O8)), RR0T(2, 1) = cos(rad(O7)) * sin(rad(O8)), RR0T(2, 2) = -cos(rad(O8)), RR0T(2, 3) = O6;
  RR0T(3, 0) = 0, RR0T(3, 1) = 0, RR0T(3, 2) = 0, RR0T(3, 3) = 1;
}

void REVERSE_R_0_T_WORKFRAME_OFFSET_4X4_MATRIX() {
  Multiply(RWF, RR0T, RR0TWF);
}

void REVERSE_R_0_6_4X4_MATRIX() {
  Multiply(RR0TWF, RITF, RR06);
}

void REVERSE_REMOVE_R_0_6_4X4_MATRIX() {
  RRR06(0, 0) = cos(rad(180)), RRR06(0, 1) = sin(rad(180)), RRR06(0, 2) = 0, RRR06(0, 3) = 0;
  RRR06(1, 0) = -sin(rad(180)) * cos(D18), RRR06(1, 1) = cos(rad(180)) * cos(D18), RRR06(1, 2) = sin(D18), RRR06(1, 3) = 0;
  RRR06(2, 0) = sin(rad(180)) * sin(D18), RRR06(2, 1) = -cos(rad(180)) * sin(D18), RRR06(2, 2) = cos(D18), RRR06(2, 3) = -E18;
  RRR06(3, 0) = 0, RRR06(3, 1) = 0, RRR06(3, 2) = 0, RRR06(3, 3) = 1;
}

void REVERSE_R_0_5_4X4_MATRIX() {
  Multiply(RR06, RRR06, RR05);
}


void WRIST_CONF_QUADRANT() {
  //IF(AND(O4>0,O5>0),1,IF(AND(O4>0,O5<0),2,IF(AND(O4<0,O5<0),3,IF(AND(O4<0,O5>0),4,))))

  if (O4 > 0 && O5 > 0) {
    V9 = 1;
  }
  else if (O4 > 0 && O5 < 0) {
    V9 = 2;
  }
  else if (O4 < 0 && O5 < 0) {
    V9 = 3;
  }
  else if (O4 < 0 && O5 > 0) {
    V9 = 4;
  }
  else {
    V9 = 0;
  }
}

void J1_ANG() {
  O13 = atan((RR05(1, 3)) / (RR05(0, 3)));

  if (V9 == 1) {
    P13 = deg(O13);
  }
  else if (V9 == 2) {
    P13 = deg(O13);
  }
  else if (V9 == 3) {
    P13 = -180 + deg(O13);
  }
  else if (V9 == 4) {
    P13 = 180 + deg(O13);
  }
  else {
    P13 = -180;
  }
}

void FWD_MID() {
  O16 = sqrt(pow((abs(RR05(1, 3))), 2) + pow((abs(RR05(0, 3))), 2)) /*FWD*/, P16 = O16 /*MID*/; //PX
  O17 = RR05(2, 3) - E13 /*FWD*/, P17 = O17 /*MID*/; //PY
  O18 = O16 - F13 /*FWD*/, P18 = -O18 /*MID*/; //PX-A1
  O19 = sqrt(pow(O17, 2) + pow(O18, 2)) /*FWD*/, P19 = sqrt((O17, 2) + (P18, 2)) /*MID*/; //PA2H
  O20 = sqrt(pow(E16, 2) + pow(F15, 2)) /*FWD*/, P20 = 20 /*MID*/; //PA3H
  O21 = deg(atan(O17 / O18)) /*FWD*/, P21 = deg(acos((pow(F14, 2) + pow(P19, 2) - pow(abs(E16), 2)) / (2 * F14 * P19))) /*MID*/; //@A
  O22 = deg(acos((pow(F14, 2) + pow(O19, 2) - pow(abs(O20), 2)) / (2 * F14 * O19))) /*FWD*/, P22 = (deg(atan(P18 / O17))) /*MID*/; //@B
  O24 = 0 /*FWD*/, P24 = 90 - (P21 + P22) /*MID*/; //@D
  if (F15 == 0) {
    O25 = 90 /*FWD*/, P25 = O25 /*MID*/; //@E
  }
  else {
    O25 = deg(atan(abs(E16) / F15)) /*FWD*/, P25 = O25 /*MID*/; //@E
  }
  O23 = 180 - deg(acos((pow(abs(O20), 2) + pow(F14, 2) - pow(O19, 2)) / (2 * abs(O20) * F14))) + (90 - O25) /*FWD*/, P23 = 180 - deg(acos((pow(abs(O20), 2) + pow(F14, 2) - pow(P19, 2)) / (2 * abs(O20) * F14))) + (90 - O25) /*MID*/; //@C
  O26 = -(O21 + O22) /*FWD*/, P26 = -180 + P24 /*MID*/; //J2_ANG
  O27 = O23 /*FWD*/, P27 = P23 /*MID*/; //J3_ANG
}

void REVERSE_OUT_PUT() {
  Q4 = P13; //J1
  if (O18 < 0) {
    Q5 = P26; //J2
  }
  else {
    Q5 = O26; //J2
  }
  if (O18 < 0) {
    Q6 = P27; //J3
  }
  else {
    Q6 = O27; //J3
  }
}

void REVERSE_J1_4X4_MATRIX() {
  RJ1(0, 0) = cos(rad(Q4)), RJ1(0, 1) = -sin(rad(Q4)) * cos(D13), RJ1(0, 2) = sin(rad(Q4)) * sin(D13), RJ1(0, 3) = F13 * cos(rad(Q4));
  RJ1(1, 0) = sin(rad(Q4)), RJ1(1, 1) = cos(rad(Q4)) * cos(D13), RJ1(1, 2) = -cos(rad(Q4)) * sin(D13), RJ1(1, 3) = F13 * sin(rad(Q4));
  RJ1(2, 0) = 0, RJ1(2, 1) = sin(D13), RJ1(2, 2) = cos(D13), RJ1(2, 3) = E13;
  RJ1(3, 0) = 0, RJ1(3, 1) = 0, RJ1(3, 2) = 0, RJ1(3, 3) = 1;
}

void REVERSE_J2_4X4_MATRIX() {
  RJ2(0, 0) = cos(rad(Q5)), RJ2(0, 1) = -sin(rad(Q5)) * cos(D14), RJ2(0, 2) = sin(rad(Q5)) * sin(D14), RJ2(0, 3) = F14 * cos(rad(Q5));
  RJ2(1, 0) = sin(rad(Q5)), RJ2(1, 1) = cos(rad(Q5)) * cos(D14), RJ2(1, 2) = -cos(rad(Q5)) * sin(D14), RJ2(1, 3) = F14 * sin(rad(Q5));
  RJ2(2, 0) = 0, RJ2(2, 1) = sin(D14), RJ2(2, 2) = cos(D14), RJ2(2, 3) = E14;
  RJ2(3, 0) = 0, RJ2(3, 1) = 0, RJ2(3, 2) = 0, RJ2(3, 3) = 1;
}

void REVERSE_J3_4X4_MATRIX() {
  RJ3(0, 0) = cos(rad((Q6) - 90)), RJ3(0, 1) = -sin(rad((Q6) - 90)) * cos(D15), RJ3(0, 2) = sin(rad((Q6) - 90)) * sin(D15), RJ3(0, 3) = F15 * cos(rad((Q6) - 90));
  RJ3(1, 0) = sin(rad((Q6) - 90)), RJ3(1, 1) = cos(rad((Q6) - 90)) * cos(D15), RJ3(1, 2) = -cos(rad((Q6) - 90)) * sin(D15), RJ3(1, 3) = F15 * sin(rad((Q6) - 90));
  RJ3(2, 0) = 0, RJ3(2, 1) = sin(D15), RJ3(2, 2) = cos(D15), RJ3(2, 3) = E15;
  RJ3(3, 0) = 0, RJ3(3, 1) = 0, RJ3(3, 2) = 0, RJ3(3, 3) = 0;
}

void REVERSE_R_0_1_4X4_MATRIX() {
  Multiply(RWF, RJ1, RR01);
}

void REVERSE_R_0_2_4X4_MATRIX() {
  Multiply(RR01, RJ2, RR02);
}

void REVERSE_R_0_3_4X4_MATRIX() {
  Multiply(RR02, RJ3, RR03);
}

void REVERSE_R_0_3_TRANSPOSED_3X3_MATRIX() {
  RR03T(0, 0) = RR03(0, 0), RR03T(0, 1) = RR03(1, 0), RR03T(0, 2) = RR03(2, 0);
  RR03T(1, 0) = RR03(0, 1), RR03T(1, 1) = RR03(1, 1), RR03T(1, 2) = RR03(2, 1);
  RR03T(2, 0) = RR03(0, 2), RR03T(2, 1) = RR03(1, 2), RR03T(2, 2) = RR03(2, 2);
}

void REVERSE_R_3_6_3X3_MATRIX() {
  RR36(0, 0) = (RR03T(0, 0) * RR05(0, 0)) + (RR03T(0, 1) * RR05(1, 0)) + (RR03T(0, 2) * RR05(2, 0)), RR36(0, 1) = (RR03T(0, 0) * RR05(0, 1)) + (RR03T(0, 1) * RR05(1, 1)) + (RR03T(0, 2) * RR05(2, 1)), RR36(0, 2) = (RR03T(0, 0) * RR05(0, 2)) + (RR03T(0, 1) * RR05(1, 2)) + (RR03T(0, 2) * RR05(2, 2));
  RR36(1, 0) = (RR03T(1, 0) * RR05(0, 0)) + (RR03T(1, 1) * RR05(1, 0)) + (RR03T(1, 2) * RR05(2, 0)), RR36(1, 1) = (RR03T(1, 0) * RR05(0, 1)) + (RR03T(1, 1) * RR05(1, 1)) + (RR03T(1, 2) * RR05(2, 1)), RR36(1, 2) = (RR03T(1, 0) * RR05(0, 2)) + (RR03T(1, 1) * RR05(1, 2)) + (RR03T(1, 2) * RR05(2, 2));
  RR36(2, 0) = (RR03T(2, 0) * RR05(0, 0)) + (RR03T(2, 1) * RR05(1, 0)) + (RR03T(2, 2) * RR05(2, 0)), RR36(2, 1) = (RR03T(2, 0) * RR05(0, 1)) + (RR03T(2, 1) * RR05(1, 1)) + (RR03T(2, 2) * RR05(2, 1)), RR36(2, 2) = (RR03T(2, 0) * RR05(0, 2)) + (RR03T(2, 1) * RR05(1, 2)) + (RR03T(2, 2) * RR05(2, 2));
}

void REVERSE_OUT_PUT2() {
  R7 = deg(atan2(RR36(1, 2), RR36(0, 2))), S7 = deg(atan2(-RR36(1, 2), -RR36(0, 2)));
  R8 = deg(atan2(+sqrt(1 - pow(RR36(2, 2), 2)), RR36(2, 2))), S8 = deg(atan2(-sqrt(1 - pow(RR36(2, 2), 2)), RR36(2, 2)));
  if (RR36(2, 1) < 0) {
    R9 = deg(atan2(-RR36(2, 1), RR36(2, 0))) - 180;
  }
  else {
    R9 = deg(atan2(-RR36(2, 1), RR36(2, 0))) + 180;
  }
  if (RR36(2, 1) < 0) {
    S9 = deg(atan2(RR36(2, 1), -RR36(2, 0))) + 180;
  }
  else {
    S9 = deg(atan2(RR36(2, 1), -RR36(2, 0))) - 180;
  }
  if (B8 > 0 && R8 > 0) {
    Q8 = R8; //J5
  }
  else {
    Q8 = S8; //J5
  }
  if (Q8 > 0) {
    Q7 = R7; //J4
  }
  else {
    Q7 = S7; //J4
  }
  if (Q8 < 0) {
    Q9 = S9; //J6
  }
  else {
    Q9 = R9; //J6
  }
}

void INVERSE_CALCULATION() {
  REVERSE_WORK_FRAME_4X4_MATRIX();
  REVERSE_R_0_T_4X4_MATRIX();
  REVERSE_R_0_T_WORKFRAME_OFFSET_4X4_MATRIX();
  REVERSE_TOOL_FRAME_4X4_MATRIX();
  REVERSE_INVERT_TOOL_FRAME_4X4_MATRIX();
  REVERSE_R_0_6_4X4_MATRIX();
  REVERSE_REMOVE_R_0_6_4X4_MATRIX();
  REVERSE_R_0_5_4X4_MATRIX();
  WRIST_CONF_QUADRANT();
  J1_ANG();
  FWD_MID();
  REVERSE_OUT_PUT();
  REVERSE_J1_4X4_MATRIX();
  REVERSE_J2_4X4_MATRIX();
  REVERSE_J3_4X4_MATRIX();
  REVERSE_R_0_1_4X4_MATRIX();
  REVERSE_R_0_2_4X4_MATRIX();
  REVERSE_R_0_3_4X4_MATRIX();
  REVERSE_R_0_3_TRANSPOSED_3X3_MATRIX();
  REVERSE_R_3_6_3X3_MATRIX();
  REVERSE_OUT_PUT2();
}

float rad(float deg) {
  return deg * 0.017453;
}

float deg(float rad) {
  return rad * 57.296;
}
