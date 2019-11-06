
// --- Mapeamento de Hardware ---
#define ENC_A PB5 // pin 13 PB5
#define ENC_B PB4 // pin 12 PB4
#define Motor_L PB3 // define pino D11
#define Motor_R PD3 // defie pino D3

#define target1   PB0  // pin 8
#define target2   PD7  // pin 7

#define  set_bit(reg, bit_reg)  (reg |= (1<<bit_reg)) // técnica de bitwise para ativar o reg especifico
#define  reset_bit(reg, bit_reg)  (reg &= ~(1<<bit_reg)) // técnica de bitwise para limpar o reg especifico

#define ENC_PORT PINB




// ========================================================================================================
// --- Protótipo das Funções ---
char read_encoder(); //Função para leitura de Rotary Encoder

void show_encoder(); //Função para mostrar de Rotary Encoder

void setDuty_Motor_L();

void setDuty_Motor_R();
// ========================================================================================================


// ======================================================================================================
//******************* PIN CHARGE INTERRUPT *****************

// Função de Tratamento de Interrupção
ISR(PCINT0_vect) {

  set_bit(PORTD, target2); //digitalWrite(target2, HIGH);
  // toggle_bit(PORTD, target2);
  show_encoder();
  reset_bit(PORTD, target2);

}

//***********************************************************





void setup() {
  Serial.begin(115200);

  //  DDRB = B00001010;
  DDRD |= (1 << Motor_L); // pinMode(Motor_L, OUTPUT);
  DDRB |= (1 << Motor_R); // pinMode(Motor_R, OUTPUT);



  //configura pino do led como saída
  DDRD |= (1 << target2); //  pinMode(target2, OUTPUT);
  DDRB |= (1 << target1); //  pinMode(target1, OUTPUT);

  //************ PIN CHARGE INTERRUPT *****************

  cli();


  //pinMode(13, INPUT_PULLUP);
  //pinMode(12, INPUT_PULLUP);

  DDRB &= ~( (1 << DDB5) | (1 << DDB4));
  PORTB |= ( (1 << PORTB5) | (1 << PORTB4));

  // Seta as "chaves" necessárias para que as interrupções cheguem ao vetor;
  PCICR |= (1 << PCIE0);
  PCMSK0 |= ( (1 << PCINT5) | (1 << PCINT4));

  sei();

  //***************************************************

  TCCR2A = 0xA3; // 1010 0011
  //TCCR2B = TCCR2B & B11111000 | B00000110;    // set timer 2 divisor to   256 for PWM frequency of   122.55 Hz

  setFrequency(1); // ~ 1 kHz

  // setDuty_Motor_L(0);
  setDuty_Motor_L(50);
  // setDuty_Motor_L(50);
  // setDuty_Motor_L(75);
  // setDuty_Motor_L(100);

  setDuty_Motor_R(80.0);



}

void loop() {


}
