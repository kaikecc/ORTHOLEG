# Controle PID usando Método Ziegler-Nichils para Controle de Velocidade do Motor DC Maxon 


### 1. INTRODUÇÃO

### 2. MODELO MATEMÁTICO MOTOR DC



</b> </b>
<p align="center">
 <b>Figura 1.</b>
 <a href="#">Circuito Equivalente de um motor DC controlado por armadura</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71666447-97ba9b00-2d3f-11ea-8d54-44e231f2bcea.png" width="600" heigth="600"> 
</p>

### 3. CONTROLADOR PID




</b> </b>
<p align="center">
 <b>Figura 2.</b>
 <a href="#">Diagrama de bloco do controlador PID</a> 
 <br><br>
<img src="https://i.pinimg.com/originals/b2/3a/3e/b23a3e0e58f4fd2bb2845351fe878368.png" width="600" heigth="600"> 
</p>

### 4. SINTONIZANDO POR ZIEGLER-NICHOLS

### 5. SIMULAÇÃO E ANÁLISE



</b> </b>
<p align="center">
 <b>Figura 6.</b>
 <a href="#">Função de Transferência do Motor</a> 
 <br><br>
<img src="http://latex.codecogs.com/gif.latex?G%28s%29%20%3D%20%5Cfrac%7B0.0302%7D%7B1.164%20*%2010%5E%7B-9%7D%20*%20s%5E%7B2%7D%20&plus;%206.705%20*%2010%5E%7B-6%7D%20*s%20&plus;%200.01794%7D" width="400" heigth="400"> 
</p>

### 6. RESULTADOS E ANÁLISE



</b> </b>
<p align="center">
 <b>Figura 7.</b>
 <a href="#">Curva de Resposta Z-N motor DC</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71667843-85436000-2d45-11ea-8f59-0db2eb9d9b0b.png" width="600" heigth="600"> 
</p>



</b> </b>
<p align="center">
 <b>Figura 8.</b>
 <a href="#">Curva de Resposta Z-N motor DC com zoom</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71667892-b754c200-2d45-11ea-8315-6d6a82db1cd5.png" width="600" heigth="600"> 
</p>


</b> </b>
<p align="center">
 <b>Figura 9.</b>
 <a href="#">Z-N Closed Loop Response</a> 
 <br><br>
<img src="https://user-images.githubusercontent.com/42541528/71667929-d3586380-2d45-11ea-8585-82ee4c63034a.png" width="600" heigth="600"> 
</p>
### 7. CONCLUSÃO