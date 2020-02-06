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
#define      n     50        //número de pontos da média móvel 



// ========================================================================================================

// ===============================================================================
// --- Protótipo da Função ---
float moving_average();       //Função para filtro de média móvel


// ===============================================================================
// --- Variáveis Globais ---
float       original,          //recebe o valor de AN0
            filtrado;          //recebe o valor original filtrado

float       numbers[n];        //vetor com os valores para média móvel



// ===============================================================================
// --- Variáveis Globais ---
float           rpm;
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

Serial.println(pulsos);
delay(200);
/*
  //Atualiza contador a cada segundo
  if (millis() - timeold >= 100)
  {
    //Desabilita interrupcao durante o calculo
    detachInterrupt(1);

   
    rpm = ((((float)abs(pulsos)) * 60000.0) / 20.0) / (float)(millis() - timeold);

    original = rpm;
    filtrado = moving_average();
    timeold = millis();
    pulsos = 0;

    //Mostra o valor de RPM no serial monitor
    Serial.print(rpm);
    Serial.print("\t");
    Serial.println(filtrado);

    //Habilita interrupcao
    attachInterrupt(1, contador, FALLING);
  }
*/
} //end loop

// ===============================================================================
// --- Desenvolvimento da Função ---
float moving_average()
{

  //desloca os elementos do vetor de média móvel
  for (int i = n - 1; i > 0; i--) numbers[i] = numbers[i - 1];

  numbers[0] = original; //posição inicial do vetor recebe a leitura original

  float acc = 0;          //acumulador para somar os pontos da média móvel

  for (int i = 0; i < n; i++) acc += numbers[i]; //faz a somatória do número de pontos


  return acc / n; //retorna a média móvel


} //end moving_average
