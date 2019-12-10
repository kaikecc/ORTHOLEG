clc
clear all

% Dados do motor
Km = 30.2 * 1E-3;  % Constante de Torque do Motor
Ra = 0.299;        % Resistência do Motor
La = 0.082 * 1E-3; % Indutância do Motor
J1 = 14.2 * 1E-6;  % Momento de Inércia do Motor
tq1 = 177 * 1E-3;  % Torque Nominal do Motor
v1 = 6940*(pi/30); % Velocidade Angular Nominal do Motor 
b1 = tq1/v1;       % Coeficiente de Viscosidade do Motor

% Dados da Caixa de Redução
N1 = 8;
N2 = 343;

J2 = 15 * 1E-6; % Momento de Inércia da Caixa de Redução
tq2 = tq1 * N2; % Torque da Caixa de Redução 
v2 = v1 / N2; % Velocidade da Caixa da Redução
b2 = tq2 / v2; % Coeficiente de Viscosidade da Caixa de Redução

% Equivalentes

Jeq = J1 + J2*(N2/N1)^2; % equivalente de cap em paral se soma
beq = (1/b1)*(1/b2)*(N2/N1)^2 / ((1/b1) + (1/b2)*(N2/N1)^2); % equivalente

s = tf('s');

P_motor = Km /(Jeq*La*s^2 + (Jeq*Ra + beq*La)*s + beq*Ra + Km^2);

%step(P_motor);

%sisotool('rlocus', P_motor);





      
