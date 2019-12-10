/* ========================================================================================================

   Curso de Arduino e AVR 153

   WR Kits Channel


   Sensor de Velocidade Encoder


   Autor: Eng. Wagner Rambo  Data: Janeiro de 2018

   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits


   Algoritmo baseado no artigo:
   https://www.arduinoecia.com.br/2016/02/sensor-de-velocidade-lm393-arduino.html


  ======================================================================================================== */


// ========================================================================================================
// --- Mapeamento de Hardware ---
#define   vcc      5
#define   gnd      4
#define   pino_D0  3
#define   analog   2
#define      n     10        //número de pontos da média móvel 



// ========================================================================================================

// ===============================================================================
// --- Protótipo da Função ---
long moving_average();       //Função para filtro de média móvel


// ===============================================================================
// --- Variáveis Globais ---
int       original,          //recebe o valor de AN0
          filtrado;          //recebe o valor original filtrado

int       numbers[n];        //vetor com os valores para média móvel



// ===============================================================================
// --- Variáveis Globais ---
int           rpm;
volatile byte pulsos;
unsigned long timeold;

//Altere o numero abaixo de acordo com o seu disco encoder
unsigned int pulsos_por_volta = 20;


// ========================================================================================================
// --- Interrupção ---
void contador()
{
  //Incrementa contador
  pulsos++;
 

}


// ========================================================================================================
// --- Configurações Iniciais ---
void setup()
{
  Serial.begin(115200);

  pinMode(vcc,    OUTPUT);
  pinMode(gnd,    OUTPUT);
  pinMode(pino_D0, INPUT);
  pinMode(analog,  INPUT);

  digitalWrite(vcc, HIGH);
  digitalWrite(gnd,  LOW);

  //Interrupcao 1 - pino digital 3
  //Aciona o contador a cada pulso
  attachInterrupt(1, contador, FALLING);
  pulsos = 0;
  rpm = 0;
  timeold = 0;

} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop()
{


  //Atualiza contador a cada segundo
  if (millis() - timeold >= 1000)
  {
    //Desabilita interrupcao durante o calculo
    detachInterrupt(1);

    rpm = ((60 * 1000 / pulsos_por_volta ) / (millis() - timeold)) * (pulsos/4);
    original = rpm;
   // filtrado = moving_average();
    timeold = millis();
    pulsos = 0;

    //Mostra o valor de RPM no serial monitor
    Serial.print("RPM = ");
    Serial.println(rpm, DEC);

    //Habilita interrupcao
    attachInterrupt(1, contador, FALLING);
  }

} //end loop

// ===============================================================================
// --- Desenvolvimento da Função ---
long moving_average()
{

  //desloca os elementos do vetor de média móvel
  for (int i = n - 1; i > 0; i--) numbers[i] = numbers[i - 1];

  numbers[0] = original; //posição inicial do vetor recebe a leitura original

  long acc = 0;          //acumulador para somar os pontos da média móvel

  for (int i = 0; i < n; i++) acc += numbers[i]; //faz a somatória do número de pontos


  return acc / n; //retorna a média móvel


} //end moving_average
