

// --- Mapeamento de Hardware ---
#define ENC_A PB5 // pin 13 PB5
#define ENC_B PB4 // pin 12 PB4
#define Motor_L PB3 // define pino D11
#define Motor_R PD3 // defie pino D3
//#define led   PB0  // pin 8

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

// --- Variáveis Globais ---
unsigned char enc_A_prev = 0x00,
              counter    = 0x00,
              ctn_T2     = 0x00,
              flag_enc   = 0x01;


// ========================================================================================================


// ======================================================================================================
// --- Constantes ---
const uint16_t T1_init = 0;
// ~ 9 us
const uint16_t T1_comp = 18;// (tempo x freq) / prescaler =
// prescaler: 8


// ======================================================================================================
// --- Interrupção ---
ISR(TIMER1_COMPA_vect)
{

  TCNT1 = T1_init;      //reinicializa TIMER1
  //PORTB ^= (1 << led);  //inverte nível lógico do pino do led
  set_bit(PORTD, PORTD7); //digitalWrite(7, HIGH);
  show_encoder();
  reset_bit(PORTD, PORTD7); //digitalWrite(7, LOW);

} //end ISR



void setup() {
  Serial.begin(115200);

  //  DDRB = B00001010;
  DDRD |= (1 << Motor_L); // pinMode(Motor_L, OUTPUT);
  DDRB |= (1 << Motor_R); // pinMode(Motor_R, OUTPUT);
  
  
  //  DDRB |= (1 << led); //  pinMode(led, OUTPUT);

  //configura pino do ENC_A, ENC_B como entrada
  DDRB &= ~(1 << ENC_A); //  pinMode(ENC_A, INPUT);
  DDRB &= ~(1 << ENC_B); // pinMode(ENC_B, INPUT);

  TCCR2A = 0xA3; // 1010 0011
  //TCCR2B = TCCR2B & B11111000 | B00000110;    // set timer 2 divisor to   256 for PWM frequency of   122.55 Hz
  setFrequency(1); // ~ 1 kHz

  // setDuty_Motor_L(0);
  setDuty_Motor_L(20);
  // setDuty_Motor_L(50);
  // setDuty_Motor_L(75);
  // setDuty_Motor_L(100);

  setDuty_Motor_R(80.0);

  //Modo de Comparação
  TCCR1A = 0;

  /*
    //Prescaler 1:256
    TCCR1B |=  (1 << CS12);
    TCCR1B &= ~(1 << CS11);
    TCCR1B &= ~(1 << CS10);
  */


  //Prescaler 1:8
  TCCR1B |=  ~(1 << CS12);
  TCCR1B &=   (1 << CS11);
  TCCR1B &=  ~(1 << CS10);

  //Inicializa Registradores
  TCNT1 = T1_init;
  OCR1A = T1_comp; // recebe as constantes de comparação

  //Habilita Interrupção do Timer1
  TIMSK1 = (1 << OCIE1A);

}

void loop() {


}
