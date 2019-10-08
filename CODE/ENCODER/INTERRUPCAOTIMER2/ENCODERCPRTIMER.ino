/* ========================================================================================================
 
   Curso de Arduino e AVR 150
   
   WR Kits Channel


   Encoder Rotativo por Interrupção

    
   Autor: Eng. Wagner Rambo  Data: Dezembro de 2017
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits


   HARDWARE Encoder Rotativo:

   +       -> 5V do Arduino
   GND     -> GND do Arduino
   DT      -> digital 8 Arduino
   CLK     -> digital 9 Arduino
   
   
======================================================================================================== */


// ========================================================================================================
// --- Mapeamento de Hardware ---
#define ENC_A 8
#define ENC_B 9
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
// --- Interrupção ---
ISR(TIMER2_OVF_vect)
{
    TCNT2=178;          // Reinicializa o registrador do Timer2

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


// ========================================================================================================
// --- Configurações Iniciais ---
void setup() 
{

     
     Serial.begin(9600);  
     
     pinMode(ENC_A, INPUT);
     pinMode(ENC_B, INPUT);
     pinMode(13, OUTPUT);
     
     //-- Configura Interrupção --
     TCCR2A = 0x00;   //Timer operando em modo normal
     TCCR2B = 0x07;   //Prescaler 1:1024
     TCNT2  = 178;    //~~ 5 ms para o overflow
     TIMSK2 = 0x01;   //Habilita interrupção do Timer2

} //end setup


// ========================================================================================================
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






