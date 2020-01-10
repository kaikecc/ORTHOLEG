# Controlador PID usando Método Ziegler-Nichols para Controle de Velocidade do Motor DC Maxon 


### 1. INTRODUÇÃO </b> </b>

Inspirar o desenvolvimento de recursos de eletrônica de potência, a motores de corrente contínua tornou-se cada vez mais útil. Atualmente, seus usos não são limitados nas aplicações automotivas (veículo elétrico), em aplicações de baixa potência usando
sistema de bateria (motor de brinquedo) ou para tração elétrica no sistemas multimaquina também. A velocidade do motor DC pode ser
ajustado em grande medida, de modo a fornecer fácil **controlabilidade** e  **alto desempenho**. Os controladores da velocidade
que são concebidos para o objetivo de controlar a velocidade do motor DC executar uma variedade de tarefas, é de várias formas convencionais e controladores numéricos, os controladores podem ser: PID Controlador, Controlador Lógico Difuso, Algoritmo Genético
técnica de otimização de enxame de partículas ou a técnica combinação entre eles: Redes Fuzzy-Neurais, Algoritmo FuzzyGenetic, Colônia Fuzzy-Formigas, Fuzzy-Swarm. Dentro 1942, Ziegler-Nichols apresentou uma fórmula de ajuste, com base no tempo de resposta e experiências.

</b> </b>
### 2. MODELO MATEMÁTICO MOTOR DC </b> </b>

Um atuador comum em sistemas de controle é o motor CC. Ele fornece movimento rotativo diretamente e, juntamente com rodas ou tambores e cabos, pode fornecer movimento de translação. O circuito equivalente elétrico da armadura e o diagrama de corpo livre do rotor são mostrados na figura 1 a seguir.

</b> </b>
<p align="center">
 <b>Figura 1.</b>
 <a href="#">Circuito Equivalente de um motor DC controlado por armadura</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71666447-97ba9b00-2d3f-11ea-8d54-44e231f2bcea.png" width="400" heigth="400"> 
</p>

</b> </b>
<p align="center">
 <b>Figura 2.</b>
 <a href="#">Circuito Equivalente do motor com caixa de redução</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71670554-f76c7280-2d4e-11ea-8361-61c6bd439939.png" width="600" heigth="800"> 
</p>


</b> </b>
<p align="center">
 <b>Figura 3.</b>
 <a href="#">Diagrama de bloco da função de transferência do motor</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71668848-4ca58580-2d49-11ea-9cd7-3c787827d6f8.png" width="600" heigth="600"> 
</p>

### 3. CONTROLADOR PID


</b> </b>
<p align="center">
 <b>Figura 4.</b>
 <a href="#">Expressão do PID</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71669052-2c29fb00-2d4a-11ea-8afd-e32bc1ca0652.png" width="300" heigth="300"> 
</p>




</b> </b>
<p align="center">
 <b>Figura 5.</b>
 <a href="#">Função de transferência do PID</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71669319-09e4ad00-2d4b-11ea-877c-5a71cc2a82ba.png" width="200" heigth="200"> 
</p>

Aumentar o ganho proporcional **K_p** tem o efeito de aumentar proporcionalmente o sinal de controle para o mesmo nível de erro. O fato de o controlador "pressionar" com mais força por um determinado nível de erro tende a fazer com que o sistema de circuito fechado reaja mais rapidamente, mas também a ultrapassar mais. Outro efeito do aumento de **K_p** é que ele tende a reduzir, mas não a eliminar, o erro de estado estacionário.

A adição de um termo derivativo ao controlador **K_d** adiciona a capacidade do controlador de "antecipar" o erro. Com um controle proporcional simples, se **K_p** for corrigido, a única maneira de aumentar o controle é se o erro aumentar. Com o controle derivativo, o sinal de controle pode se tornar grande se o erro começar a subir, mesmo enquanto a magnitude do erro ainda seja relativamente pequena. Essa antecipação tende a adicionar amortecimento ao sistema, diminuindo assim o excesso. A adição de um termo derivado, no entanto, não afeta o erro de estado estacionário.

A adição de um termo integral ao controlador **K_i** tende a ajudar a reduzir o erro no estado estacionário. Se houver um erro persistente e constante, o integrador cria e constrói, aumentando assim o sinal de controle e diminuindo o erro. Uma desvantagem do termo integral, no entanto, é que ele pode tornar o sistema mais lento (e oscilatório), pois quando o sinal de erro muda de sinal, pode demorar um pouco para o integrador "relaxar".

</b> </b>
<p align="center">
 <b>Figura 6.</b>
 <a href="#">Diagrama de bloco do controlador PID</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71668812-21bb3180-2d49-11ea-87fb-d4767ecacd70.png" width="600" heigth="600"> 
</p>

### 4. SINTONIZANDO POR ZIEGLER-NICHOLS



</b> </b>
<p align="center">
 <b>Figura 7.</b>
 <a href="#">Modelo da planta</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71669820-c5f2a780-2d4c-11ea-96dc-fcd5769c3b53.png" width="200" heigth="200"> 
</p>




</b> </b>
<p align="center">
 <b>Figura 8.</b>
 <a href="#">Modelo da curva para o método Z-N</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71669888-f8040980-2d4c-11ea-9139-226c0046f2d6.png" width="400" heigth="400"> 
</p>




</b> </b>
<p align="center">
 <b>Tabela 1.</b>
 <a href="#">Z-N Primeiro Método</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71670080-98f2c480-2d4d-11ea-93b4-8fef8efd4450.png" width="300" heigth="300"> 
</p>

</b> </b>
<p align="center">
 <b>Tabela 2.</b>
 <a href="#">Z-N Segundo Método</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71670175-e1aa7d80-2d4d-11ea-91cd-cdee83ded587.png" width="300" heigth="300"> 
</p>

### 5. SIMULAÇÃO E ANÁLISE

* Dados do motor: </b> </b>

* **Kt =** 30.2 * 1E-3;  % Constante de Torque do Motor (m.N / A)
* **Kb =** pi / 317*30;  % back emf constant (V.s / rad)
* **Ra =** 0.299;        % Resistência do Motor (R)
* **La =** 0.082 * 1E-3; % Indutância do Motor (H)
* **J1 =** 14.2 * 1E-6;  % Momento de Inércia do Motor (kg.m^3)
* **tq1 =** 177 * 1E-3;  % Torque Nominal do Motor (m.N)
* **v1 =** 6940*(pi/30); % Velocidade Angular Nominal do Motor (rad / s) 
* **b1 =** (3.14*30*1E-3) / pi;  % Coeficiente de Viscosidade do Motor (m.N / rad/s) 


</b> </b>
<p align="center">
 <b>Figura 9.</b>
 <a href="#">Diagrama de bloco do controle do motor DC</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71670675-65b13500-2d4f-11ea-971a-a5ab3a60d9c7.png" width="400" heigth="400"> 
</p>

</b> </b>
<p align="center">
 <b>Figura 10.</b>
 <a href="#">Função de Transferência do Motor</a> 
 <br><br>
<img src="http://latex.codecogs.com/gif.latex?G%28s%29%20%3D%20%5Cfrac%7B0.0302%7D%7B1.164%20*%2010%5E%7B-9%7D%20*%20s%5E%7B2%7D%20&plus;%206.705%20*%2010%5E%7B-6%7D%20*s%20&plus;%200.01794%7D" width="400" heigth="400"> 
</p>

</b> </b>
<p align="center">
 <b>Figura 11.</b>
 <a href="#">Função de Transferência PID</a> 
 <br><br>
<img src="http://latex.codecogs.com/gif.latex?K%28s%29%20%3D%20%5Cfrac%7B2.485*10%5E%7B-12%7D*s%5E%7B2%7D%20&plus;%200.005992*s%20&plus;%205.074%7D%7B0.001181*s%7D" width="400" heigth="400"> 
</p>

### 6. RESULTADOS E ANÁLISE



</b> </b>
<p align="center">
 <b>Figura 11.</b>
 <a href="#">Curva de Resposta Z-N motor DC</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71667843-85436000-2d45-11ea-8f59-0db2eb9d9b0b.png" width="600" heigth="800"> 
</p>



</b> </b>
<p align="center">
 <b>Figura 12.</b>
 <a href="#">Curva de Resposta Z-N motor DC com zoom</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71667892-b754c200-2d45-11ea-8315-6d6a82db1cd5.png" width="600" heigth="800"> 
</p>


</b> </b>
<p align="center">
 <b>Figura 13.</b>
 <a href="#">Z-N Closed Loop Response</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71667929-d3586380-2d45-11ea-8585-82ee4c63034a.png" width="600" heigth="800"> 
</p>



</b> </b>
<p align="center">
 <b>Figura 14.</b>
 <a href="#">Resposta ao degrau</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71669514-ac049500-2d4b-11ea-83ba-de9f1af4a15a.png" width="600" heigth="600"> 
</p>

### 7. CONCLUSÃO </b> </b>
