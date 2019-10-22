/* ======================================================================================================

   Curso de Arduino WR Kits Channel

   Aplicação para os Timers do Atmega328p (Arduino UNO, Duemilanove e outros)


   Autor: Eng. Wagner Rambo  Data: Março de 2018


   www.wrkits.com.br | facebook.com/wrkits | youtube.com/canalwrkits


  ==================================================================================================== */



// ========================================================================================================
// --- Mapeamento de Hardware ---
#define ENC_A PB5 // pin 13 PB5
#define ENC_B PB4 // pin 12 PB4

//#define led   PB2  // pin 9

#define ENC_PORT PINB



// ========================================================================================================
// --- Protótipo das Funções ---
char read_encoder(); //Função para leitura de Rotary Encoder

void show_encoder();

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
// ~ 1 ms
const uint16_t T1_comp = 63;// (tempo x freq) / prescaler =
// prescaler: 256


// ======================================================================================================
// --- Interrupção ---
ISR(TIMER1_COMPA_vect)
{

  TCNT1 = T1_init;      //reinicializa TIMER1
  // PORTB ^= (1 << led);  //inverte nível lógico do pino do led

  show_encoder();

} //end ISR


// ======================================================================================================
// --- Configurações Iniciais ---
void setup()
{


  Serial.begin(115200);




  //configura pino do led como saída

  // DDRB |= (1 << led); //  pinMode(led, OUTPUT);
  //configura pino do ENC_A, ENC_B como entrada

  DDRB &= ~(1 << ENC_A); //  pinMode(ENC_A, INPUT);
  DDRB &= ~(1 << ENC_B); // pinMode(ENC_B, INPUT);

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


} //end setup


// ======================================================================================================
// --- Loop Infinito ---
void loop()
{
  



} //end loop
