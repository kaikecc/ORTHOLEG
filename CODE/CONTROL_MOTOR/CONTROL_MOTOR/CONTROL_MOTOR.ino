#include <Wire.h>
#include "PID.cpp"
#include "IOpins.h"



#define  set_bit(reg, bit_reg)  (reg |= (1<<bit_reg))    // técnica de bitwise para ativar o reg especifico
#define  toggle_bit(reg, bit_reg) (reg  ^= (1<<bit_reg)) // técnica de bitwise para alternar os estados
#define  reset_bit(reg, bit_reg)  (reg &= ~(1<<bit_reg)) // técnica de bitwise para limpar o reg especifico


//**************************************** I2C *********************************
#define SLAVE_ADDRESS 0x18

//********************************************************************************

//********************************* VARIÁVEIS GLOBAIS **************************************************

PID posPid(0.0, 0.0001, 0.0, P_ON_E, DIRECT);// (kP, kI, kD, direcao)

volatile long pulse_number = 0x00, counter = 0x00;
volatile double rpm = 0.0;

/********************************************************************************************************/

// =============================   Protótipo das Funções =================================================

void setDuty_Motor_L();
void setDuty_Motor_R();
void counter_pulses();
void setFrequency(char option);
double AngleCounts(double graus);

// ========================================================================================================

//************************* TIMER1 ISR ********************************************************************

// --- Constantes ---
const uint16_t T1_init = 0;
// ~10ms
const uint16_t T1_comp = 63;// (tempo x freq) / prescaler =
// prescaler: 256

const double tempo  = ((double)T1_comp * 256.0) / 16.0E6; // ~ 100ms

//const double pulsos_por_volta = 500.0;
//const double reducao = 43.0;

// --- Interrupção ---
ISR(TIMER1_COMPA_vect)
{
  TCNT1 = T1_init; // reinicializa TIMER1

  //  rpm = (((double(abs(pulse_number)) / 2.0 ) * 60.0) / (double)pulsos_por_volta) / tempo;
  //  pulse_number = 0;

  posPid.addNewSample(counter);
  posPid.process();

  posPid.pid > 0.0 ? PORTB &= ~(1 << lmdirpin) : PORTB |= (1 << lmdirpin);
  ((posPid.pid < 7.305205) && (posPid.pid > -7.305205))  ? PORTB |= (1 << lmbrkpin) : PORTB &= ~(1 << lmbrkpin);

  setDuty_Motor_L(abs(posPid.pid) + (100.0 * (0.0 + 0.177 * 3140.0) / (317.0 * 24.0)));
  
  Serial.println(posPid.pid);
 
} //end ISR

//**********************   END ISR *******************************

// Função de Tratamento de Interrupção
ISR(PCINT0_vect) {
  counter_pulses();

}// end ISR

void setup() {
  Serial.begin(115200);
  //  Wire.begin(SLAVE_ADDRESS );
  //  Wire.onRequest(requestEvent);
  //  Wire.onReceive(receiveEvent);
  //  Wire.setClock(3400000);

  DDRB |= (1 << lmpwmpin); // pinMode(lmpwmpin, OUTPUT);
  DDRB |= (1 << lmbrkpin); // pinMode(lmbrkpin, OUTPUT);
  DDRB |= (1 << lmdirpin); // pinMode(lmdirpin, OUTPUT);
  DDRC &= ~(1 << lmcurpin); // pinMode(lmcurpin, INPUT);

  DDRD |= (1 << rmpwmpin); // pinMode(rmpwmpin, OUTPUT);
  DDRD |= (1 << rmbrkpin); // pinMode(lmbrkpin, OUTPUT);
  DDRD |= (1 << rmdirpin); // pinMode(lmdirpin, OUTPUT);
  DDRC &= ~(1 << rmcurpin); // pinMode(lmcurpin, INPUT);

  // DDRD |= (1 << PD7); //  pinMode(target, OUTPUT);

  //************************** PCINT CHARGE INTERRUPT **********************************

  cli();

  DDRB &= ~( (1 << DDB5) | (1 << DDB4));
  PORTB |= ( (1 << PORTB5) | (1 << PORTB4));

  // Seta as "chaves" necessárias para que as interrupções cheguem ao vetor;
  PCICR |= (1 << PCIE0);
  // PCMSK0 |= ( (1 << PCINT5) | (1 << PCINT4));
  PCMSK0 |= (1 << PCINT5); // INTERRUPÇAO É ATIVADA NA MUDANÇA DE ESTADO DO PINO 13

  sei();

  //******************************** END PCINT ******************************************

  // **************************** CONFIG. TIMER1 ****************************************
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

  TCCR2A = 0xA3; // 1010 0011 -- Configura operação e fast PWM, utilizando registrador
  setFrequency(1); // ~  62.5 kHz

  setDuty_Motor_L(0.0);// CONTROLE DO MOTOR ESQUERDO
  //  PORTB |= (1 << lmdirpin); // SENTIDO ANTI-HORÁRIO MOTOR ESQUERDO
  //  PORTB &= ~(1 << lmdirpin); // SENTIDO HORÁRIO MOTOR ESQUERDO
  //  PORTD &= ~(1 << lmbrkpin); //  ensure breaks left are off, but     to  control    pin    HIGH = Brake

  //  setDuty_Motor_R(0.0); // CONTROLE DO MOTOR DIREITO
  //  PORTD |= (1 << rmdirpin); // SENTIDO HORÁRIO MOTOR DIREITO
  //  PORTD &= ~(1 << rmdirpin); // SENTIDO ANTI-HORÁRIO MOTOR DIREITO
  //  PORTB &= ~(1 << rmbrkpin); // ensure breaks right are off, but     to    control    pin    HIGH = Brake

  posPid.setSampleTime(tempo);
  posPid.setSetPoint(AngleCounts(360.0)); // SEMPRE POSITIVO OS VALORES POR CAUSA DO ENCODER INCREMETAL ONDE A ORIGEM É DEFINADA COM ZERO
  posPid.SetOutputLimit(-100.0, 100.0);

}
void loop() {}
