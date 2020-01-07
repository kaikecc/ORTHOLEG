#include <Wire.h>

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
#define lmcurpin  6   //  A6 - left  motor current      monitor    pin    0 - 1023         -20A to +20A   

#define  set_bit(reg, bit_reg)  (reg |= (1<<bit_reg))    // técnica de bitwise para ativar o reg especifico
#define  toggle_bit(reg, bit_reg) (reg  ^= (1<<bit_reg)) // técnica de bitwise para alternar os estados
#define  reset_bit(reg, bit_reg)  (reg &= ~(1<<bit_reg)) // técnica de bitwise para limpar o reg especifico

#define SAMPLE_DELAY 1000  //  this gets 1 reading per second.

#define SLAVE_ADDRESS 0x18

//******************** VARIÁVEIS GLOBAIS ********************

//PID constants
double kp = 5.07443237; // 5231928;
double ki = 4.29735426E03; //3433757E03;
double kd = 2.10487472E-04; //3675934E-04;

unsigned long currentTime, previousTime;
double elapsedTime;
double error;
double lastError;
double input, output, setPoint;
double cumError, rateError;

volatile unsigned int pulse_number = 0;
volatile unsigned int   rpm = 0;

/***********************************************************/


// ========================================================================================================
// --- Protótipo das Funções ---
void setDuty_Motor_L();
void setDuty_Motor_R();
void counter_pulses();
void setFrequency(char option);
double computePID(double inp);
// ========================================================================================================

//******************* PIN CHARGE INTERRUPT *****************

// Função de Tratamento de Interrupção
ISR(PCINT0_vect) {
 
  counter_pulses();
  
}

//*****************   END ISR *******************************

// --- Constantes ---
const uint16_t T1_init = 0;
// ~ 100 ms
const uint16_t T1_comp = 6250;// (tempo x freq) / prescaler =
// prescaler: 256

// --- Interrupção ---
ISR(TIMER1_COMPA_vect)
{
   set_bit(PORTD, PORTD7);
  //Altere o numero abaixo de acordo com o seu disco encoder
  unsigned int pulsos_por_volta = 500;

  TCNT1 = T1_init;      //reinicializa TIMER1
  
  rpm = (((pulse_number * 60) / pulsos_por_volta) / 0.1)/4;
  pulse_number = 0;
  Serial.println(rpm);
  reset_bit(PORTD, PORTD7);

} //end ISR


void setup() {

  Serial.begin(115200);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveData);

  DDRD |= (1 << lmpwmpin); // pinMode(lmpwmpin, OUTPUT);
  DDRD |= (1 << lmbrkpin); // pinMode(lmbrkpin, OUTPUT);
  DDRD |= (1 << lmdirpin); // pinMode(lmdirpin, OUTPUT);
  DDRC &= ~(1 << lmcurpin); // pinMode(lmcurpin, INPUT);

  DDRB |= (1 << rmpwmpin); // pinMode(rmpwmpin, OUTPUT);
  DDRB |= (1 << rmbrkpin); // pinMode(lmbrkpin, OUTPUT);
  DDRB |= (1 << rmdirpin); // pinMode(lmdirpin, OUTPUT);
  DDRC &= ~(1 << rmcurpin); // pinMode(lmcurpin, INPUT);

  DDRD |= (1 << PORTD7); // pinMode(lmdirpin, OUTPUT);
  //************* PIN CHARGE INTERRUPT *************************

  cli();

  DDRB &= ~( (1 << DDB5) | (1 << DDB4)); // Seta D12, D13 como entrada;
  PORTB |= ( (1 << PORTB5) | (1 << PORTB4));// Liga Pull-up

  // Seta as "chaves" necessárias para que as interrupções cheguem ao vetor
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT5); // INTERRUPÇAO É ATIVADA NA MUDANÇA DE ESTADO DO PINO 13

  sei();

  //***************************** END PCINT ************************************


 // ************************** CONFIG. TIMER1 *******************************************
  //Modo de Comparação
  TCCR1A = 0;


  //Prescaler 1:256
  TCCR1B |=  (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS10);


  /*
    //Prescaler 1:8
    TCCR1B |=  ~(1 << CS12);
    TCCR1B &=   (1 << CS11);
    TCCR1B &=  ~(1 << CS10);
  */

  /*
    //Prescaler 1:1
    TCCR1B |=  ~(1 << CS12);
    TCCR1B &=   ~(1 << CS11);
    TCCR1B &=   (1 << CS10);
  */
  //Inicializa Registradores
  TCNT1 = T1_init;
  OCR1A = T1_comp; // recebe as constantes de comparação

  //Habilita Interrupção do Timer1
  TIMSK1 = (1 << OCIE1A);


  //****************************** END TIMER1 *************************************

  TCCR2A = 0xA3; // 1010 0011
  setFrequency(1); // ~  62.5 kHz

  setDuty_Motor_L(10.0);
  PORTD |= (1 << lmdirpin); // SENTIDO HORÁRIO MOTOR ESQUERDO
  //  PORTD &= ~(1 << lmdirpin); // SENTIDO ANTI-HORÁRIO MOTOR ESQUERDO
  //  PORTD &= ~(1 << lmbrkpin); //  ensure breaks left are off, but     to  control    pin    HIGH = Brake

  setDuty_Motor_R(0.0);
  PORTB |= (1 << rmdirpin); // SENTIDO HORÁRIO MOTOR DIREITO
  //  PORTB &= ~(1 << rmdirpin); // SENTIDO ANTI-HORÁRIO MOTOR DIREITO
  //  PORTB &= ~(1 << rmbrkpin); // ensure breaks right are off, but     to    control    pin    HIGH = Brake

  // setPoint = 750.0; // rpm
}

void loop() {
  

  // setDuty_Motor_L(setPoint * (1.0 / 317.0) * (100.0 / 24.0)); // Kb = 317 (V / rpm)

}
