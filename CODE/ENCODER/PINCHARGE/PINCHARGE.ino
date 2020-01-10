#define  set_bit(reg, bit_reg)  (reg |= (1<<bit_reg)) // técnica de bitwise para ativar o reg especifico
#define  reset_bit(reg, bit_reg)  (reg &= ~(1<<bit_reg)) // técnica de bitwise para limpar o reg especifico
#define toggle_bit(reg, bit_reg) (reg  ^= (1<<bit_reg))

#define ENC_PORT PINB
#define ENC_A PB5 // D13 - encoder A
#define ENC_B PB4 // D12 - encoder B
#define led   PB3  // pin 11

volatile int pulse_number = 0x00;


//******************* PIN CHARGE INTERRUPT *****************

// Função de Tratamento de Interrupção
ISR(PCINT0_vect) {

  set_bit(PORTB, led); //digitalWrite(7, HIGH);
  // toggle_bit(PORTB, led);
  // show_encoder();
  counter_pulses();
  Serial.println(pulse_number);
  reset_bit(PORTB, led);

}

//***********************************************************


void setup() {
  Serial.begin(115200);

  //configura pino do led como saída
  DDRB |= (1 << led); //  pinMode(led, OUTPUT);

  //************ PIN CHARGE INTERRUPT *****************

  cli();


  //pinMode(13, INPUT_PULLUP);
  //pinMode(12, INPUT_PULLUP);

  DDRB &= ~( (1 << DDB5) | (1 << DDB4));
  PORTB |= ( (1 << PORTB5) | (1 << PORTB4));

  // Seta as "chaves" necessárias para que as interrupções cheguem ao vetor;
  PCICR |= (1 << PCIE0);
  // PCMSK0 |= ( (1 << PCINT5) | (1 << PCINT4));
  PCMSK0 |= (1 << PCINT5); // INTERRUPÇAO É ATIVADA NA MUDANÇA DE ESTADO DO PINO 13

  sei();

  //***************************************************
}

void loop() {



}
