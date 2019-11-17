
// --- Mapeamento de Hardware ---
#define ENC_A PB5 // D13 - encoder A
#define ENC_B PB4 // D12 - encoder B
#define ENC_PORT PINB // mascara do PORTB

#define rmpwmpin PB3  // D11 - right motor pulse width  modulation pin    0 - 255          Speed and Brake 
#define rmbrkpin PB1  //  D9 - right motor brake        control    pin    HIGH = Brake 
#define rmdirpin PB2  // D10 - right motor direction    control    pin    HIGH = Forward   Low = Reverse
#define rmcurpin 7   //  A7 - right motor current      monitor    pin    0 - 1023         -20A to +20A   

#define lmpwmpin PD3  // D3 - left  motor pulse width  modulation pin     0 - 255          Speed and Brake
#define lmbrkpin PD4  //  D4 - left  motor brake        control    pin    HIGH = Brake 
#define lmdirpin PD2  //  D2 - left  motor direction    control    pin    HIGH = Forward   Low = Reverse
#define lmcurpin  6  //  A6 - left  motor current      monitor    pin    0 - 1023         -20A to +20A   

#define target1   PB0  // D8 - marcador 1
#define target2   PD7  // D7 - marcador 2

#define  set_bit(reg, bit_reg)  (reg |= (1<<bit_reg)) // técnica de bitwise para ativar o reg especifico
#define  toggle_bit(reg, bit_reg) (reg  ^= (1<<bit_reg)) // técnica de bitwise para alternar os estados
#define  reset_bit(reg, bit_reg)  (reg &= ~(1<<bit_reg)) // técnica de bitwise para limpar o reg especifico

#define turn_break 43E3 // para couter_pulses -- 2*500(CPR)*43 - Uma volta no eixo depois da redução (1:43)

//86E3  para show_encoder-- 4*500(CPR)*43 - Uma volta no eixo depois da redução (1:43)

volatile unsigned long cpp = 0;
volatile long  pulse_number = 0;

// ========================================================================================================
// --- Protótipo das Funções ---
char read_encoder(); //Função para leitura de Rotary Encoder

void show_encoder(); //Função para mostrar de Rotary Encoder

void setDuty_Motor_L();

void setDuty_Motor_R();

void counter_pulses();
// ========================================================================================================



//******************* PIN CHARGE INTERRUPT *****************

// Função de Tratamento de Interrupção
ISR(PCINT0_vect) {

  set_bit(PORTB, target1); //digitalWrite(target2, HIGH);
  // toggle_bit(PORTD, target2);
  // if (PINB & (1 << PINB5))
  //  show_encoder(); // D13 mudou de LOW para HIGH;
  counter_pulses();
  reset_bit(PORTB, target1); //digitalWrite(target2, LOW);

}

//***********************************************************


void setup() {
  Serial.begin(115200);

  //  DDRB = B00001010;
  DDRD |= (1 << lmpwmpin); // pinMode(lmpwmpin, OUTPUT);
  DDRD |= (1 << lmbrkpin); // pinMode(lmbrkpin, OUTPUT);
  DDRD |= (1 << lmdirpin); // pinMode(lmdirpin, OUTPUT);
  DDRC &= ~(1 << lmcurpin); // pinMode(lmcurpin, INPUT);


  DDRB |= (1 << rmpwmpin); // pinMode(rmpwmpin, OUTPUT);
  DDRB |= (1 << rmbrkpin); // pinMode(lmbrkpin, OUTPUT);
  DDRB |= (1 << rmdirpin); // pinMode(lmdirpin, OUTPUT);
  DDRC &= ~(1 << rmcurpin); // pinMode(lmcurpin, INPUT);


  //configura pinos do marcadores como saída
  DDRD |= (1 << target2); //  pinMode(target2, OUTPUT);
  DDRB |= (1 << target1); //  pinMode(target1, OUTPUT);

  //************ PIN CHARGE INTERRUPT *******************

  cli();



  DDRB &= ~( (1 << DDB5) | (1 << DDB4)); // Seta D12, D13 como entrada;
  //pinMode(13, INPUT_PULLUP);
  //pinMode(12, INPUT_PULLUP);
  PORTB |= ( (1 << PORTB5) | (1 << PORTB4));// Liga Pull-up

  // Seta as "chaves" necessárias para que as interrupções cheguem ao vetor;
  PCICR |= (1 << PCIE0);
  // PCMSK0 |= ( (1 << PCINT5) | (1 << PCINT4));
  PCMSK0 |= (1 << PCINT5);

  sei();

  //******************************************************

  TCCR2A = 0xA3; // 1010 0011
  //TCCR2B = TCCR2B & B11111000 | B00000110;    // set timer 2 divisor to   256 for PWM frequency of   122.55 Hz

  setFrequency(1); // ~  62.5 kHz

  setDuty_Motor_L(50.0);
  PORTD |= (1 << lmdirpin); // SENTIDO HORÁRIO MOTOR ESQUERDO
  //  PORTD &= ~(1 << lmdirpin); // SENTIDO ANTI-HORÁRIO MOTOR ESQUERDO
  // PORTD &= ~(1 << lmbrkpin); //  ensure breaks left are off, but     to  control    pin    HIGH = Brake


  setDuty_Motor_R(0.0);
  PORTB |= (1 << rmdirpin); // SENTIDO HORÁRIO MOTOR DIREITO
  //  PORTB &= ~(1 << rmdirpin); // SENTIDO ANTI-HORÁRIO MOTOR DIREITO
  // PORTB &= ~(1 << rmbrkpin); // ensure breaks right are off, but     to    control    pin    HIGH = Brake

}

void loop() {
  

  if (abs(pulse_number) > turn_break) {
    set_bit(PORTD, target2);
    setDuty_Motor_L(0.0);
  }

}
