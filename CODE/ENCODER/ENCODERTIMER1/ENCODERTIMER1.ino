/* ======================================================================================================
   
   Curso de Arduino WR Kits Channel
   
   Aplicação para os Timers do Atmega328p (Arduino UNO, Duemilanove e outros)
   
    
   Autor: Eng. Wagner Rambo  Data: Março de 2018
    
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/canalwrkits

    
==================================================================================================== */



// ========================================================================================================
// --- Mapeamento de Hardware ---
#define ENC_A 9
#define ENC_B 10
#define ENC_PORT PINB


// ========================================================================================================
// --- Protótipo das Funções ---
char read_encoder();                                    //Função para leitura de Rotary Encoder


// ========================================================================================================
// --- Variáveis Globais ---
unsigned char enc_A_prev = 0x00,
              counter    = 0x00,
              ctn_T2     = 0x00,
              flag_enc   = 0x01;


// ========================================================================================================

// ======================================================================================================
// --- Mapeamento de Hardware ---
#define   led   PB5


// ======================================================================================================
// --- Constantes ---
const uint16_t T1_init = 0;
const uint16_t T1_comp = 313;//31250;


// ======================================================================================================
// --- Interrupção ---
ISR(TIMER1_COMPA_vect)
{
  
  TCNT1 = T1_init;      //reinicializa TIMER1
  PORTB ^= (1 << led);  //inverte nível lógico do pino do led

   static unsigned char counter = 0; //this variable will be changed by encoder input
    char tmpdata;
    /**/
    tmpdata = read_encoder();
    if( tmpdata ) 
    {
      Serial.print("Counter value: ");
      Serial.println(counter, DEC);
      
      counter += tmpdata;
    }
  
} //end ISR


// ======================================================================================================
// --- Configurações Iniciais ---
void setup()
{

  
     Serial.begin(9600);  
     
     pinMode(ENC_A, INPUT);
     pinMode(ENC_B, INPUT);
     
   DDRB |= (1 << led);  //configura pino do led como saída

   //Modo de Comparação
   TCCR1A = 0;

   //Prescaler 1:256
   TCCR1B |=  (1 << CS12);
   TCCR1B &= ~(1 << CS11);
   TCCR1B &= ~(1 << CS10);

   //Inicializa Registradores
   TCNT1 = T1_init;
   OCR1A = T1_comp;

   //Habilita Interrupção do Timer1
   TIMSK1 = (1 << OCIE1A);
   
  
} //end setup


// ======================================================================================================
// --- Loop Infinito ---
void loop()
{
    
  
  
} //end loop

//=============================================================================
// --- Desenvolvimento das Funções ---
char read_encoder()                              //Função para leitura de Rotary Encoder
{
  static char enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
  static unsigned char old_AB = 0;
  /**/
  old_AB <<= 2;                   //remember previous state
  old_AB |= ( ENC_PORT & 0x03 );  //add current state
  return ( enc_states[( old_AB & 0x0f )]);

} //end read_encoder
