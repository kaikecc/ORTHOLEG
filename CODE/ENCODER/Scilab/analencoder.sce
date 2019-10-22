
arq = uigetfile("*.txt","C:\Users\kaike\Documents\READSERIAL\","Escolha um arquivo .txt: "); // Funcao para pegar um arquivo
valor2 = fscanfMat(arq);// pega o arquivo de formato especificado 

tempo = 0:0.001:((length(valor2)-1)*0.001);
plot(tempo,valor2)
