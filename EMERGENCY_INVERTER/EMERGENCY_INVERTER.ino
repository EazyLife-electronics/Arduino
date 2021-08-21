float F = 50; //modulation frequency
float f = 30395.1367; //carrier frequency
float N = 0;
float angle_incr = 0;
int lower_dutyC = 5; //lowest dutycycle
int upper_dutyC = 250; //highest duty sycle
int dutyC_diff;
int dutycycle[480], i = 0;
float deg = 0.0;
const float pi = 3.142857142857143;
float sine = 0;
bool OK = 0;

void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  dutyC_diff = upper_dutyC - lower_dutyC;
  N = f / (2 * F);
  angle_incr = 180 / N;
  for (int i = 0; i < (N + 1); i ++) {
    sine = sin((deg * pi) / 180);
    dutycycle[i] = (sine * dutyC_diff) + lower_dutyC;
    deg += angle_incr;
    Serial.print(dutycycle[i]);
    Serial.print(",");
  }
  Serial.println("  *  ");
  i = 0;
  cli();// stop interrupts
  TCCR0A = 0; //reset the value
  TCCR0B = 0; //reset the value
  TCNT0 = 0; //reset the value
  //0b allow me to write bits in binary
  TCCR0A = 0b10100001; //phase correct pwm mode
  TCCR0B = 0b00000001; //no prescaler
  TCCR1A = 0; //reset the value
  TCCR1B = 0; //reset the value
  TCNT1 = 0; //reset the value
  OCR1A = 509; // compare match value
  TCCR1B = 0b00001001; //WGM12 bit is 1 and no prescaler
  TIMSK1 |= (1 << OCIE1A);
  sei();// enable interrupts
}
ISR(TIMER1_COMPA_vect) { //interrupt when timer 1 match with OCR1A value
  if (!OK) {
    digitalWrite(4, HIGH);
    digitalWrite(7, LOW);
    OCR0A = dutycycle[i]; //enable pin 6 to corresponding duty cycle
    OCR0B = 0; //enable pin 5 to corresponding duty cycle
  }
  else if (OK) {
    digitalWrite(7, HIGH);
    digitalWrite(4, LOW);
    OCR0B = dutycycle[i]; //enable pin 5 to corresponding duty cycle
    OCR0A = 0; //enable pin 6 to corresponding duty cycle
  }
  i++;
  Serial.print(dutycycle[i]);
  Serial.print(",");
  if (i >= N) {
    i = 0;
    OK = !OK;
  }
}
void loop() {

}
