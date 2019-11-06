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

O código foi construído através de interrupção por mudança de estado nos pinos digitais D12 e D13 que chamará a função [PCINT](https://portal.vidadesilicio.com.br/pcint-interrupcoes-por-mudanca-de-estado/) que está ligado ao PORTB e habilita uma das três ISRs relacionados os três registradores PCMSJ0, PCMSK1 e PCMSK2. O código abaixo chama PCINT0_vect que é o vetor de interrupção do PORTB.

Ao organizar o código por interrupção garante maior controle nos processos de execução de tarefas.

Essa sessão define todos os pinos que serão utilizado pelo ATmega328. Os pino target target2 é pino que 
servirá como marcador de tempo na entrada e saída de função de leitura de encoder através do osciloscópio.

<details>
<summary>"ISR(PCINT0_vect)"</summary>

``` ino

// Função de Tratamento de Interrupção
ISR(PCINT0_vect) {

  set_bit(PORTD, target2); //digitalWrite(target2, HIGH);
  // toggle_bit(PORTD, target2);
  show_encoder();
  reset_bit(PORTD, target2); //digitalWrite(target2, LOW);

}

```
</details>

<details>
<summary>"read_encoder()"</summary>
``` ino
//=============================================================================
// --- Desenvolvimento das Funções ---
char read_encoder()                              //Função para leitura de Rotary Encoder
{
  static char enc_states[] = {
    0, -1, 1, 0,
    1, 0, 0, -1,
    -1, 0, 0, 1,
    0, 1, -1, 0
  };

  static unsigned char old_AB = 0;
  /**/
  old_AB >>= 2;                   //remember previous state


  old_AB |= ( ENC_PORT & 0x30 );  //add current state

  return ( enc_states[( old_AB & 0x0f )]);

} //end read_encoder

}
```
</details>

<details>
<summary>"show_encoder()"</summary>
``` ino
//=============================================================================
// --- Desenvolvimento das Funções ---
void show_encoder() {

  static unsigned char counter = 0; // variavel pra armazenar valor do encoder
  char tmpdata; // dado temporario


  tmpdata = read_encoder();

  if ( tmpdata )
  {

    set_bit(PORTB, target1); //digitalWrite(7, HIGH);
    counter += tmpdata;
    reset_bit(PORTB, target1);

  }
}
//=============================================================================
```
</details>
``` ino

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



<p align="center">
 <b>Figura 5.</b>
 <a href="#">PWM do direito e esquerdo</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/68331085-1cc46380-00b3-11ea-8c35-2e43ef6f0bd9.png" width="600" heigth="600"> 
</p>
