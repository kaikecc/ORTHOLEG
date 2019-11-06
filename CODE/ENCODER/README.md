# ENCODER POR QUADRATURA

### 1. INTRODUÇÃO
Em algumas aplicações de movimento exigem pouca precisão e nenhum feedback. Outros, principalmente industriais, exigem uma maneira robusta de acompanhar dados confiáveis e precisos sobre velocidade, posição e direção.

Os motores CC de passo, escovado ou sem escova não fornecem nenhum tipo de feedback, exceto quando estão equipados com um codificador ou sensor de hall.

#### O que é um ENCODER? </b> </b>

> [Encoder](https://www.hitecnologia.com.br/blog/o-que-%C3%A9-encoder-para-que-serve-como-escolher-como-interfacear) são dispositivos/sensores eletro-mecânicos cuja funcionalidade é transformar posição em sinal elétrico digital. Com a utilização de encoders é possível quantizar distâncias, controlar velocidades, medir ângulos, número de rotações, realizar posicionamentos, rotacionar braços robóticos e etc.

### 2. MATERIAIS E MÉTODOS


#### Encoder HEDL 5540

Esse encoder, Figura 1, possui 500 [CPR](https://www.cuidevices.com/blog/what-is-encoder-ppr-cpr-and-lpr) (Contagem Por Revolução) e refere-se ao número de estados decodificados em quadratura que existem entre as duas saídas A e B. A frequência máxima de operação é de 100kHz com velocidade em torno de 12000 rpm.


<p align="center">
 <b>Figura 1.</b>
 <a href="#">Encoder HEDL 5540</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/68326961-382b7080-00ab-11ea-95a4-aa0eb6415b51.png" width="600" heigth="600"> 
</p>


<p align="center">
 <b>Figura 2.</b>
 <a href="#">Ficha técninca do encoder</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/68327411-0f57ab00-00ac-11ea-9560-f6f9de8a119e.png" width="600" heigth="600"> 
</p>

#### 2.1 ANÁLISE DO CÓDIGO

Essa sessão define todos os pinos que serão utilizado pelo ATmega328. Os pinos target1 e target2 são pinos que 
servirão como marcadores de tempo na entrada e saída de função de leitura de encoder através do osciloscópio.

``` ino
// --- Mapeamento de Hardware ---
#define ENC_A PB5 // pin 13 PB5
#define ENC_B PB4 // pin 12 PB4
#define Motor_L PB3 // define pino D11
#define Motor_R PD3 // defie pino D3

#define target1   PB0  // pin 8
#define target2   PD7  // pin 7

#define  set_bit(reg, bit_reg)  (reg |= (1<<bit_reg)) // técnica de bitwise para ativar o reg especifico
#define  reset_bit(reg, bit_reg)  (reg &= ~(1<<bit_reg)) // técnica de bitwise para limpar o reg especifico

#define ENC_PORT PINB

```

``` ino
// ========================================================================================================
// --- Protótipo das Funções ---
char read_encoder(); //Função para leitura de Rotary Encoder

void show_encoder(); //Função para mostrar de Rotary Encoder

void setDuty_Motor_L();

void setDuty_Motor_R();
// ========================================================================================================
```

``` ino
// =========================================================
//******************* PIN CHARGE INTERRUPT *****************

// Função de Tratamento de Interrupção
ISR(PCINT0_vect) {

  set_bit(PORTD, target2); //digitalWrite(target2, HIGH);
  // toggle_bit(PORTD, target2);
  show_encoder();
  reset_bit(PORTD, target2);

}

//***********************************************************
```

``` ino

void setup() {
  Serial.begin(115200);

  //  DDRB = B00001010;
  DDRD |= (1 << Motor_L); // pinMode(Motor_L, OUTPUT);
  DDRB |= (1 << Motor_R); // pinMode(Motor_R, OUTPUT);
  //configura pino do led como saída
  DDRD |= (1 << target2); //  pinMode(target2, OUTPUT);
  DDRB |= (1 << target1); //  pinMode(target1, OUTPUT);

  //************ PIN CHARGE INTERRUPT *****************
  cli();

  //pinMode(13, INPUT_PULLUP);
  //pinMode(12, INPUT_PULLUP);

  DDRB &= ~( (1 << DDB5) | (1 << DDB4));
  PORTB |= ( (1 << PORTB5) | (1 << PORTB4));

  // Seta as "chaves" necessárias para que as interrupções cheguem ao vetor;
  PCICR |= (1 << PCIE0);
  PCMSK0 |= ( (1 << PCINT5) | (1 << PCINT4));

  sei();

  //******************************************************

  TCCR2A = 0xA3; // 1010 0011
  //TCCR2B = TCCR2B & B11111000 | B00000110;// set timer 2 divisor to   256 for PWM frequency of 122.55 Hz

  setFrequency(1); // ~ 1 kHz

  
  setDuty_Motor_L(50);  
  setDuty_Motor_R(80.0);

}
```

``` ino
void loop() {


}
```
### 3. RESULTADOS



<p align="center">
 <b>Figura 3.</b>
 <a href="#">Pulsos do gerador de sinais</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/68328832-cbb27080-00ae-11ea-9c52-c89a5d196f2c.png" width="600" heigth="600"> 
</p>


<p align="center">
 <b>Figura 4.</b>
 <a href="#">Os marcados target1 e target2</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/68328912-f8ff1e80-00ae-11ea-9b9d-9f79a39d9f77.png" width="600" heigth="600"> 
</p>
