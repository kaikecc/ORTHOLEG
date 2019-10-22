 
n=300 // plot 300 data points from serial port "/dev/ttyACM0"
//overwrite = 0;
h=openserial(05,"115200,n,8,1")//,overwrite = %t)
arq = uigetfile("*.txt","C:\Users\kaike\Desktop\ORTHOLEG\CODE\ENCODER\Scilab\","Salvar arquivo .txt: "); // Funcao para pegar um arquivo
i=1;

//  Cabecalho = [" Metodo Simplex "; "z x1 x2 x3 x4 x5 x6 = b"];
while i < n
    
data(i) = strtod(readserial(h)); // char to number

plot(i, data(i),'-'); // real time plot 

drawnow(); // show data
disp(data(i))
//sleep(1000)
i = i + 1;
end
closeserial()
//fprintfMat(arq,data(i),"%5.2f");



