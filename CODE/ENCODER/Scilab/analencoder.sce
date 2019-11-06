clc
clear all
arq = uigetfile("*.txt","C:\Users\kaike\Documents\READSERIAL\","Escolha um arquivo .txt: "); // Funcao para pegar um arquivo
counter = fscanfMat(arq);// pega o arquivo de formato especificado 

tempo = 0:0.00000968:((length(counter)-1)*0.00000968);
plot(tempo,counter,'r')
xgrid

f = [0:100:100000];
CPT = 500;
rpm = (f.*60) ./ CPT;

plot(f, rpm)

xgrid

d_C = [0, 25, 50, 75, 100];
fq = [0, 25E3, 38.9E3, 48.2E3, 54.9E3];

T=10; %Period
D=5; %Duration
N=10; %Number of pulses

x=linspace(0,T*N,10000);
d=[0:T:T*N];
y=pulstran(x,d,'rectpuls',D);
plot(x,y);
ylim([-1,2]);