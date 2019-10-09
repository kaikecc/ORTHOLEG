
// "Estrutura do Timer2 Arduino Uno"
// Modified By: Kaike Castro
// By: Wagner Rambo, Wr Kits
// https://www.youtube.com/watch?v=H-xzS8DZWZY
// https://robu.in/run-rotary-encoder-arduino-code/

//these pins can not be changed 2/3 are special pins
#define encoderPin1 12
#define encoderPin2 13

// ========================================================================================================
// --- Variáveis Globais ---

volatile int lastEncoded = 0;
volatile long encoderValue = 0;
unsigned int encoderValor = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;
// ========================================================================================================


// ========================================================================================================
// --- Protótipo das Funções ---
int updateEncoder();

// ========================================================================================================


// --- Rotina de Interrupção ---
ISR(TIMER2_OVF_vect)
{
  TCNT2 = 209;        // Reinicializa o registrador do Timer2

  encoderValor = updateEncoder();

  Serial.println(encoderValor);

}


// ========================================================================================================


// --- Configurações Iniciais ---
void setup()
{
  Serial.begin(9600);
  pinMode(encoderPin1, INPUT_PULLUP);
  pinMode(encoderPin2, INPUT_PULLUP);

  TCCR2A = 0x00;   //Timer operando em modo normal
  TCCR2B = 0x07;   //Prescaler 1:1024
  TCNT2  = 209;    //3 ms overflow again
  TIMSK2 = 0x01;   //Habilita interrupção do Timer2

} //end setup

// ========================================================================================================
// --- Loop Infinito ---
void loop()
{
  //Aguarda Interrupção...

  // Estouro = Timer2_cont x prescaler x ciclo de máquina

  // Ciclo de máquina = 1/Fosc = 1/16E6 = 62,5ns = 62,5E-9s

  // Estouro = (256 - 100) x 1024 x 62,5E-9 = 9,98ms ~ 10ms
  // Estouro = (256 - 178) x 1024 x 62,5E-9 = 4,99ms ~ 5ms
  // Estouro = (256 - 209) x 1024 x 62,5E-9 = 4,99ms ~ 3ms


} //end loop

// ========================================================================================================

// --- Desenvolvimento das Funções ---
int updateEncoder() {
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time

  return encoderValue;
} //end read_encoder
