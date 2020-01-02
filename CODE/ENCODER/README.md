# LEITURA DO ENCODER HEDL 5540 PELA PLACA T'REX

### 1. INTRODUÇÃO
Em algumas aplicações de movimento exigem pouca precisão e nenhum feedback. Outros, principalmente industriais, exigem uma maneira robusta de acompanhar dados confiáveis e precisos sobre velocidade, posição e direção.

Os motores CC de passo, escovado ou sem escova não fornecem nenhum tipo de feedback, exceto quando estão equipados com um codificador ou sensor de hall.

#### O que é um ENCODER? </b> </b>

> [Encoder](https://www.hitecnologia.com.br/blog/o-que-%C3%A9-encoder-para-que-serve-como-escolher-como-interfacear) são dispositivos/sensores eletro-mecânicos cuja funcionalidade é transformar posição em sinal elétrico digital. Com a utilização de encoders é possível quantizar distâncias, controlar velocidades, medir ângulos, número de rotações, realizar posicionamentos, rotacionar braços robóticos e etc.

### 2. MATERIAIS E MÉTODOS


#### 2.1 Fixa Técnica do Encoder HEDL 5540

Esse encoder, Figura 1, possui 500 [CPR](https://www.cuidevices.com/blog/what-is-encoder-ppr-cpr-and-lpr) (Contagem Por Revolução) e refere-se ao número de estados decodificados em quadratura que existem entre as duas saídas A e B. A frequência máxima de operação é de 100kHz com velocidade em torno de 12000 rpm.


<p align="center">
 <b>Figura 1.</b>
 <a href="#">Encoder HEDL 5540</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/68326961-382b7080-00ab-11ea-95a4-aa0eb6415b51.png" width="600" heigth="800"> 
</p>


<p align="center">
 <b>Figura 2.</b>
 <a href="#">Ficha técninca do encoder</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/68327411-0f57ab00-00ac-11ea-9560-f6f9de8a119e.png" width="600" heigth="800"> 
</p>

#### 2.2 Implementação do código


<p align="center">
 <b>Figura 3.</b>
 <a href="#">Ficha técninca do encoder</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71665188-b1a5af00-2d3a-11ea-8802-d961810d53c9.png" width="600" heigth="800"> 
</p>

### 3. RESULTADOS


<p align="center">
 <b>Figura 4.</b>
 <a href="#">Pulsos do encoder na frequência máxima</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71664911-a30ac800-2d39-11ea-9e70-dcf6bb2ac736.png" width="600" heigth="600"> 
</p>


<p align="center">
 <b>Figura 5.</b>
 <a href="#">Track de pulsos pela função implentada no arduino</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71664940-ca619500-2d39-11ea-9b5e-395f7cb5966f.png" width="600" heigth="600"> 
</p>

