
#define Motor_L PB3
#define Motor_R PD3

#define POT PC5

void setDuty_Motor_L();
void setDuty_Motor_R();

int adc = 0;

void setup() {
  Serial.begin(115200);

  //  DDRB = B00001010;
  DDRD |= (1 << Motor_L); // pinMode(Motor_L, OUTPUT);
  DDRB |= (1 << Motor_R); // pinMode(Motor_R, OUTPUT);
  PINC =~ (1 << POT); // pinMode(POT, INPUT);

  TCCR2A = 0xA3; // 1010 0011
  //TCCR2B = TCCR2B & B11111000 | B00000110;    // set timer 2 divisor to   256 for PWM frequency of   122.55 Hz
  setFrequency(2);

  setDuty_Motor_L(5.0);
  setDuty_Motor_R(80.0);


}

void loop() {

   adc = analogRead(POT);

   adc = map(adc, 0, 1023, 1, 100);

   setDuty_Motor_L(adc);

   Serial.println(adc);

}
