clear all, close all, clc

% Dados do motor
Kt = 30.2 * 1E-3;  % Constante de Torque do Motor (m.N / A)
Kb = 30 / 317*pi;  % back emf constant (V.s / rad)
Ra = 0.299;        % Resist�ncia do Motor (R)
La = 0.082 * 1E-3; % Indut�ncia do Motor (H)
J1 = 14.2 * 1E-6;  % Momento de In�rcia do Motor (kg.m^3)
tq1 = 177 * 1E-3;  % Torque Nominal do Motor (m.N)
v1 = 6940*(pi/30); % Velocidade Angular Nominal do Motor (rad / s) 
b1 = 1 / (((3.14 / 1E-3) * pi) / 30);  % Coeficiente de Viscosidade do Motor (m.N / rad/s) 

% Dados da Caixa de Redu��o
N1 = 8;
N2 = 343;

J2 = 15 * 1E-6; % Momento de In�rcia da Caixa de Redu��o (kg.m^3)
tq2 = 15; % Torque da Caixa de Redu��o Max. continuous torque (m.N)
v2 = v1 / N2; % Velocidade da Caixa da Redu��o
b2 = tq2 / v2; % Coeficiente de Viscosidade da Caixa de Redu��o

% Equivalentes

Jeq = J1 + J2*(N1/N2)^2; % equivalente de cap em paral se soma
beq = b1 + b2*(N1/N2)^2; % equivalente

s = tf('s');

a = J1*La;
b = (J1*Ra + b1*La);
c =  b1*Ra + Kb*Kt;

%a = Jeq*La;
%b = (Jeq*Ra + beq*La);
%c = beq*Ra + Kb*Kt;

V_motor = Kt /(a*s*s + b*s + c);

P_motor = Kt / (s*(a*s*s + b*s + c));

pidTuner(P_motor)
