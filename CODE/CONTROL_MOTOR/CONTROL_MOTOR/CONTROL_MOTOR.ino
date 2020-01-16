#include "PID.cpp"

// --- Mapeamento de Hardware ---
#define ENC_A PB5 // D13 - encoder A
#define ENC_B PB4 // D12 - encoder B
#define ENC_PORT PINB

#define rmpwmpin PB3  // D11 - right motor pulse width  modulation pin    0 - 255          Speed and Brake 
#define rmbrkpin PB1  //  D9 - right motor brake        control    pin    HIGH = Brake 
#define rmdirpin PD2  // D10 - right motor direction    control    pin    HIGH = Forward   Low = Reverse
#define rmcurpin 7   //  A7 - right motor current      monitor    pin    0 - 1023         -20A to +20A   

#define lmpwmpin PD3  // D3 - left  motor pulse width  modulation pin     0 - 255          Speed and Brake
#define lmbrkpin PD4  //  D4 - left  motor brake        control    pin    HIGH = Brake 
#define lmdirpin PB2  //  D2 - left  motor direction    control    pin    HIGH = Forward   Low = Reverse
#define lmcurpin  6   //  A6 - left  motor current      monitor    pin    0 - 1023         -20A to +20A   

#define  set_bit(reg, bit_reg)  (reg |= (1<<bit_reg))    // técnica de bitwise para ativar o reg especifico
#define  toggle_bit(reg, bit_reg) (reg  ^= (1<<bit_reg)) // técnica de bitwise para alternar os estados
#define  reset_bit(reg, bit_reg)  (reg &= ~(1<<bit_reg)) // técnica de bitwise para limpar o reg especifico

//********************************* VARIÁVEIS GLOBAIS **************************************************


volatile long pulse_number = 0x00;
volatile long counter = 0x00;
volatile double rpm = 0.0;
volatile double speedHz = 0.0;
/********************************************************************************************************/

// =============================   Protótipo das Funções =================================================

void setDuty_Motor_L();
void setDuty_Motor_R();
void counter_pulses();
void setFrequency(char option);

// ========================================================================================================

// Função de Tratamento de Interrupção
ISR(PCINT0_vect) {
  counter_pulses();
}// end ISR

//************************* TIMER1 ISR **************************

// --- Constantes ---
const uint16_t T1_init = 0;
// ~ 0.275 ms
const uint16_t T1_comp = 17;// (tempo x freq) / prescaler =
// prescaler: 256

double tempo  = ((double)T1_comp * 256.0) / 16.0E6; // ~ 0.275 ms

PID meuPid(0.0, 147.3728, 0.0, tempo);

// --- Interrupção ---
ISR(TIMER1_COMPA_vect)
{
  //Altere o numero abaixo de acordo com o seu disco encoder
  static double pulsos_por_volta = 500.0;

  TCNT1 = T1_init;      //reinicializa TIMER1

  rpm = (((double(abs(pulse_number)) / 2.0 ) * 60.0) / pulsos_por_volta) / tempo;
  //  speedHz = abs(pulse_number) / (pulsos_por_volta * tempo * 2.0);
  pulse_number = 0;

  meuPid.addNewSample(rpm * (PI / 30));

  setDuty_Motor_L(meuPid.process());

} //end ISR



//**********************   END ISR *******************************

void setup() {

  Serial.begin(115200);

  DDRD |= (1 << lmpwmpin); // pinMode(lmpwmpin, OUTPUT);
  DDRD |= (1 << lmbrkpin); // pinMode(lmbrkpin, OUTPUT);
  DDRB |= (1 << lmdirpin); // pinMode(lmdirpin, OUTPUT);
  DDRC &= ~(1 << lmcurpin); // pinMode(lmcurpin, INPUT);

  DDRB |= (1 << rmpwmpin); // pinMode(rmpwmpin, OUTPUT);
  DDRB |= (1 << rmbrkpin); // pinMode(lmbrkpin, OUTPUT);
  DDRD |= (1 << rmdirpin); // pinMode(lmdirpin, OUTPUT);
  DDRC &= ~(1 << rmcurpin); // pinMode(lmcurpin, INPUT);

  //************************** PCINT CHARGE INTERRUPT **********************************

  cli();

  DDRB &= ~( (1 << DDB5) | (1 << DDB4));
  PORTB |= ( (1 << PORTB5) | (1 << PORTB4));

  // Seta as "chaves" necessárias para que as interrupções cheguem ao vetor;
  PCICR |= (1 << PCIE0);
  // PCMSK0 |= ( (1 << PCINT5) | (1 << PCINT4));
  PCMSK0 |= (1 << PCINT5); // INTERRUPÇAO É ATIVADA NA MUDANÇA DE ESTADO DO PINO 13

  sei();

  //******************************* END PCINT *******************************************


  // ************************** CONFIG. TIMER1 *******************************************
  //Modo de Comparação
  TCCR1A = 0;

  //Prescaler 1:256
  TCCR1B |=  (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS10);

  //Inicializa Registradores
  TCNT1 = T1_init;
  OCR1A = T1_comp; // recebe as constantes de comparação

  //Habilita Interrupção do Timer1
  TIMSK1 = (1 << OCIE1A);

  //****************************** END TIMER1 ********************************************

  TCCR2A = 0xA3; // 1010 0011
  setFrequency(1); // ~  62.5 kHz

  setDuty_Motor_L(10.0);// CONTROLE DO MOTOR ESQUERDO
  // PORTB |= (1 << lmdirpin); // SENTIDO ANTI-HORÁRIO MOTOR ESQUERDO
  PORTB &= ~(1 << lmdirpin); // SENTIDO HORÁRIO MOTOR ESQUERDO
  //  PORTD &= ~(1 << lmbrkpin); //  ensure breaks left are off, but     to  control    pin    HIGH = Brake

  // setDuty_Motor_R(0.0); // CONTROLE DO MOTOR DIREITO
  // PORTD |= (1 << rmdirpin); // SENTIDO HORÁRIO MOTOR DIREITO
  //  PORTD &= ~(1 << rmdirpin); // SENTIDO ANTI-HORÁRIO MOTOR DIREITO
  //  PORTB &= ~(1 << rmbrkpin); // ensure breaks right are off, but     to    control    pin    HIGH = Brake

  meuPid.setSetPoint(250.0 * (PI / 30)); // 250 rpm
  meuPid.SetOutputLimit(0.0, 100.0);

  //setDuty_Motor_L(100 * (250.0 + 0.177 * 3140.0) / (317.0 * 24.0));

}


void loop() {

  if (abs(counter) > 20 * 43000) setDuty_Motor_L(0.0); // DÁ UMA VOLTA

}
