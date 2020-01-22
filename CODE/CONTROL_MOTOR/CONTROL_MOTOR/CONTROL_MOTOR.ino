#include <Wire.h>
#include <stdlib.h>
class PID {
  public:

    double error;
    double sample;
    double lastSample;
    double kP, kI, kD;
    double P , I , D;
    double pid;
    double deltaTime;
    double outMin, outMax;
    double setPoint, Output;
    double ITerm, dInput;


    PID(double _kP, double _kI, double _kD) {

      if (_kD < 0 || _kI < 0 || _kD < 0) return;

      kP = _kP;
      kI = _kI;
      kD = _kD;

    }

    void addNewSample(double _sample) {

      sample = _sample;

    }

    void setSetPoint(double _setPoint) {
      setPoint = _setPoint;
    }

    void SetOutputLimit(double Min, double Max)
    {

      if (Min > Max) return;
      outMin = Min;
      outMax = Max;

      if (Output > outMax) Output = outMax;
      else if (Output < outMin) Output = outMin;

      if (ITerm > outMax) ITerm = outMax;
      else if (ITerm < outMin) ITerm = outMin;
    }

    double process(double _deltaTime) {

      deltaTime = _deltaTime;
      // Implementação P I D

      error = setPoint - sample;

      ITerm += (kI * error) * deltaTime;

      if (ITerm > outMax) ITerm = outMax;
      else if (ITerm < outMin) ITerm = outMin;

      dInput = (sample - lastSample);

      //P
      P = error * kP;

      //I
      I = ITerm;

      //D
      D = (kD * dInput) / deltaTime;

      // Soma tudo
      pid = P + I + D;

      Output = pid +  (100 * (setPoint + 0.177 * 3140.0) / (317.0 * 24.0));

      if (Output > outMax) Output = outMax;
      else if (Output < outMin) Output = outMin;

      lastSample = sample;

      return Output;
    }
};


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


//**************************************** I2C ********************************
#define SLAVE_ADDRESS 0x18


String inString = "";
double speeD = 0.0F;
//********************************************************************************

//********************************* VARIÁVEIS GLOBAIS **************************************************

PID meuPid(0.0, 0.5, 0.0);

volatile long pulse_number = 0x00;
volatile long counter = 0x00;
volatile double rpm = 0.0;

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
// ~ 100ms
const uint16_t T1_comp = 6250;// (tempo x freq) / prescaler =
// prescaler: 256

const double tempo  = ((double)T1_comp * 256.0) / 16.0E6; // ~ 0.275 ms


// --- Interrupção ---
ISR(TIMER1_COMPA_vect)
{
  set_bit(PORTD, PD7);
  //Altere o numero abaixo de acordo com o seu disco encoder
  static double pulsos_por_volta = 500.0;

  TCNT1 = T1_init;      //reinicializa TIMER1

  rpm = (((double(abs(pulse_number)) / 2.0 ) * 60.0) / pulsos_por_volta) / tempo;

  pulse_number = 0;

  meuPid.addNewSample(rpm * (PI / 30.0));
  meuPid.process(tempo);
  //  setDuty_Motor_L(meuPid.Output);



  reset_bit(PORTD, PD7);
} //end ISR

//**********************   END ISR *******************************

void setup() {

  Serial.begin(115200);
  Wire.begin(SLAVE_ADDRESS );
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  Wire.setClock(3400000);

  DDRD |= (1 << lmpwmpin); // pinMode(lmpwmpin, OUTPUT);
  DDRD |= (1 << lmbrkpin); // pinMode(lmbrkpin, OUTPUT);
  DDRB |= (1 << lmdirpin); // pinMode(lmdirpin, OUTPUT);
  DDRC &= ~(1 << lmcurpin); // pinMode(lmcurpin, INPUT);

  DDRB |= (1 << rmpwmpin); // pinMode(rmpwmpin, OUTPUT);
  DDRB |= (1 << rmbrkpin); // pinMode(lmbrkpin, OUTPUT);
  DDRD |= (1 << rmdirpin); // pinMode(lmdirpin, OUTPUT);
  DDRC &= ~(1 << rmcurpin); // pinMode(lmcurpin, INPUT);

  DDRD |= (1 << PD7); //  pinMode(target2, OUTPUT);

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

  TCCR2A = 0xA3; // 1010 0011
  setFrequency(1); // ~  62.5 kHz

  setDuty_Motor_L(double(speeD));// CONTROLE DO MOTOR ESQUERDO
  // PORTB |= (1 << lmdirpin); // SENTIDO ANTI-HORÁRIO MOTOR ESQUERDO
  PORTB &= ~(1 << lmdirpin); // SENTIDO HORÁRIO MOTOR ESQUERDO
  //  PORTD &= ~(1 << lmbrkpin); //  ensure breaks left are off, but     to  control    pin    HIGH = Brake

  // setDuty_Motor_R(0.0); // CONTROLE DO MOTOR DIREITO
  // PORTD |= (1 << rmdirpin); // SENTIDO HORÁRIO MOTOR DIREITO
  //  PORTD &= ~(1 << rmdirpin); // SENTIDO ANTI-HORÁRIO MOTOR DIREITO
  //  PORTB &= ~(1 << rmbrkpin); // ensure breaks right are off, but     to    control    pin    HIGH = Brake

  meuPid.setSetPoint(0.0 * (PI / 30.0)); // 200 rpm
  meuPid.SetOutputLimit(0.0, 100.0);

}


void loop() {

  if (abs(counter) > 20 * 43000) setDuty_Motor_L(0.0); // DÁ UMA VOLTA
  
 

}
