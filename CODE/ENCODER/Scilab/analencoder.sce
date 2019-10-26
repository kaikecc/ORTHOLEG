
arq = uigetfile("*.txt","C:\Users\kaike\Documents\READSERIAL\","Escolha um arquivo .txt: "); // Funcao para pegar um arquivo
counter = fscanfMat(arq);// pega o arquivo de formato especificado 

tempo = 0:0.000001:((length(counter)-1)*0.000001);
plot(tempo,counter,'r')
