// COM19

// ***************************************

#define rmpwmpin PD3  // D3 - right motor pulse width  modulation pin    0 - 255          Speed and Brake 
#define rmbrkpin PD4  //  D4 - right motor brake        control    pin    HIGH = Brake 
#define rmdirpin PD2  // D10 - right motor direction    control    pin    HIGH = Forward   Low = Reverse
#define rmcurpin 7   //  A7 - right motor current      monitor    pin    0 - 1023         -20A to +20A   

#define lmpwmpin PB3  // D11 - left  motor pulse width  modulation pin     0 - 255          Speed and Brake
#define lmbrkpin PB1  //  D9 - left  motor brake        control    pin    HIGH = Brake 
#define lmdirpin PB2  //  D2 - left  motor direction    control    pin    HIGH = Forward   Low = Reverse
#define lmcurpin  6   //  A6 - left  motor current      monitor    pin    0 - 1023         -20A to +20A    

#define voltspin     PC3  //  A3 - battery voltage          1V = 33.57        30V = 1007

// *******************************************

void setDuty_Motor_L();
void setDuty_Motor_R();


void setup() {
  Serial.begin(115200);

  DDRB |= (1 << lmpwmpin); // pinMode(lmpwmpin, OUTPUT);
  DDRB |= (1 << lmbrkpin); // pinMode(lmbrkpin, OUTPUT);
  DDRB |= (1 << lmdirpin); // pinMode(lmdirpin, OUTPUT);
  DDRC &= ~(1 << lmcurpin); // pinMode(lmcurpin, INPUT);

  DDRD |= (1 << rmpwmpin); // pinMode(rmpwmpin, OUTPUT);
  DDRD |= (1 << rmbrkpin); // pinMode(lmbrkpin, OUTPUT);
  DDRD |= (1 << rmdirpin); // pinMode(lmdirpin, OUTPUT);
  DDRC &= ~(1 << rmcurpin); // pinMode(lmcurpin, INPUT);

  DDRC &= ~(1 << voltspin); // pinMode(voltspin, INPUT);



  //TCCR2B = TCCR2B & B11111000 | B00000001; pwmfreq=1;    // set timer 2 divisor to    1 for PWM frequency of  31250.000000000 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000010; pwmfreq=2;    // set timer 2 divisor to    8 for PWM frequency of   3906.250000000 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000011; pwmfreq=3;    // set timer 2 divisor to   32 for PWM frequency of    976.562500000 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000100; pwmfreq=4;    // set timer 2 divisor to   64 for PWM frequency of    488.281250000 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000101; pwmfreq=5;    // set timer 2 divisor to  128 for PWM frequency of    244.140625000 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000110; pwmfreq = 6;  // set timer 2 divisor to  256 for PWM frequency of    122.070312500 Hz
  //TCCR2B = TCCR2B & B11111000 | B00000111; pwmfreq=7;    // set timer 2 divisor to 1024 for PWM frequency of     30.517578125 Hz

  TCCR2A = 0xA3; // 1010 0011
  //TCCR2B = TCCR2B & B11111000 | B00000110;    // set timer 2 divisor to   256 for PWM frequency of   122.55 Hz
  setFrequency(1); // ~ 1 kHz

  setDuty_Motor_L(10.0);// CONTROLE DO MOTOR ESQUERDO
  //PORTB |= (1 << lmdirpin); // SENTIDO ANTI-HORÁRIO MOTOR ESQUERDO
    PORTB &= ~(1 << lmdirpin); // SENTIDO HORÁRIO MOTOR ESQUERDO
  //  PORTD &= ~(1 << lmbrkpin); //  ensure breaks left are off, but     to  control    pin    HIGH = Brake

  //  setDuty_Motor_R(0.0); // CONTROLE DO MOTOR DIREITO
  //  PORTD |= (1 << rmdirpin); // SENTIDO HORÁRIO MOTOR DIREITO
  //  PORTD &= ~(1 << rmdirpin); // SENTIDO ANTI-HORÁRIO MOTOR DIREITO
  //  PORTB &= ~(1 << rmbrkpin); // ensure breaks right are off, but     to    control    pin    HIGH = Brake
}



void loop() {



}
