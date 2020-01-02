# LEITURA DO ENCODER HEDL 5540 PELA PLACA T'REX

### 1. INTRODUÇÃO
Em algumas aplicações de movimento exigem pouca precisão e nenhum feedback. Outros, principalmente industriais, exigem uma maneira robusta de acompanhar dados confiáveis e precisos sobre velocidade, posição e direção.

Os motores CC de passo, escovado ou sem escova não fornecem nenhum tipo de feedback, exceto quando estão equipados com um codificador ou sensor de hall.

#### O que é um ENCODER? </b> </b>

> [Encoder](https://www.hitecnologia.com.br/blog/o-que-%C3%A9-encoder-para-que-serve-como-escolher-como-interfacear) são dispositivos/sensores eletro-mecânicos cuja funcionalidade é transformar posição em sinal elétrico digital. Com a utilização de encoders é possível quantizar distâncias, controlar velocidades, medir ângulos, número de rotações, realizar posicionamentos, rotacionar braços robóticos e etc.

### 2. MATERIAIS E MÉTODOS </b> </b>


#### 2.1 Fixa Técnica do Encoder HEDL 5540 </b> </b>

Esse encoder, Figura 1, possui 500 [CPR](https://www.cuidevices.com/blog/what-is-encoder-ppr-cpr-and-lpr) (Contagem Por Revolução) e refere-se ao número de estados decodificados em quadratura que existem entre as duas saídas A e B. A frequência máxima de operação é de 100kHz com velocidade em torno de 12000 rpm.

</b> </b>
<p align="center">
 <b>Figura 1.</b>
 <a href="#">Encoder HEDL 5540</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/68326961-382b7080-00ab-11ea-95a4-aa0eb6415b51.png" width="600" heigth="800"> 
</p>

</b> </b>
<p align="center">
 <b>Figura 2.</b>
 <a href="#">Ficha técnica do encoder</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/68327411-0f57ab00-00ac-11ea-9560-f6f9de8a119e.png" width="600" heigth="800"> 
</p>

#### 2.2 Implementação do código </b> </b>

O desenvolvimento do código para a leitura dos pulsos do encoder foi feita otimizando a mémoria e tempo de execução e com isso a técnica de [PCINT](https://portal.vidadesilicio.com.br/pcint-interrupcoes-por-mudanca-de-estado/) que utiliza interrupção por mudança de estado do pino escolhido foi a melhor encontrada para a implementação do algotimo. Na Figura 3 mostra o diagrama do código e dentro do retângulo vermelho a função **COUNTER PULSES** responsável pela incrementação ou decrementação dos pulsos do encoder. 

</b> </b>

<p align="center">
 <b>Figura 3.</b>
 <a href="#">Diagrama de Funcionamento</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71665188-b1a5af00-2d3a-11ea-8802-d961810d53c9.png" width="600" heigth="800"> 
</p>

### 3. RESULTADOS </b> </b>

Ao analisar no osciloscópio os pulsos do encoder foi estudado a frequência máxima de rotação do motor maxon [198867](https://www.maxongroup.com/medias/sys_master/root/8833416495134/19-EN-136.pdf) submetido a uma tensão de 20V 10A e com isso resultando uma frequência na faixa 67.6 kHz a 70 kHz como mostra Figura 4. 

<p align="center">
 <b>Figura 4.</b>
 <a href="#">Pulsos do encoder na frequência máxima</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71664911-a30ac800-2d39-11ea-9e70-dcf6bb2ac736.png" width="600" heigth="600"> 
</p>

Ainda no osciloscópio foi testado a função **COUNTER PULSES** que no início do código e no fim foi adicionado um marcador que muda o estado de um pino digital para assim analisar o tempo de execução e desempenho quando o motor está na sua máxima velocidade e com isso a Figura 5 mostra em **VERDE** o rastreio por meio do pino e em **AMARELO** o canal A do encoder e pode-se perceber que há um certo atrado de em torno de 2 us em relação ao pulso do canal.

</b> </b>

<p align="center">
 <b>Figura 5.</b>
 <a href="#">Track de pulsos pela função implentada no arduino</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71664940-ca619500-2d39-11ea-9b5e-395f7cb5966f.png" width="600" heigth="600"> 
</p>


</b> </b>
### 4. CONCLUSÃO </b> </b>
