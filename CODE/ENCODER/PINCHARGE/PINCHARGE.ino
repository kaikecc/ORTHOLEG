#define  set_bit(reg, bit_reg)  (reg |= (1<<bit_reg)) // técnica de bitwise para ativar o reg especifico
#define  reset_bit(reg, bit_reg)  (reg &= ~(1<<bit_reg)) // técnica de bitwise para limpar o reg especifico
#define toggle_bit(reg, bit_reg) (reg  ^= (1<<bit_reg))
#define ENC_PORT PINB

#define led   PB3  // pin 11



//******************* PIN CHARGE INTERRUPT *****************

// Função de Tratamento de Interrupção
ISR(PCINT0_vect) {

    set_bit(PORTB, led); //digitalWrite(7, HIGH);
 // toggle_bit(PORTB, led);
  show_encoder();
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
  PCMSK0 |= ( (1 << PCINT5) | (1 << PCINT4));

  sei();

  //***************************************************
}

void loop() {
  
  

}
