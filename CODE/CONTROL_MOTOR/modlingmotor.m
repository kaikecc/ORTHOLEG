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


a = J1*La;
b = J1*Ra + b1*La;
c = b1*Ra + Km^2;

s = tf('s');
P_motor = Km /(J1*La*s^2 + (J1*Ra + b1*La)*s + b1*Ra + Km^2);

% Find the root using FZERO

format long

[y,t] = step(P_motor);
h = mean(diff(t));
dy = gradient(y, h);                                            % Numerical Derivative
[~,idx] = max(dy);                                              % Index Of Maximum
b = [t([idx-1,idx+1]) ones(2,1)] \ y([idx-1,idx+1]);            % Regression Line Around Maximum Derivative
tv = [-b(2)/b(1); (1-b(2))/b(1)];                               % Independent Variable Range For Tangent Line Plot
f = [tv ones(2,1)] * b;                                         % Calculate Tangent Line

figure
plot(t, y)
hold on
plot(tv, f, '-g')                                               % Tangent Line
plot(t(idx), y(idx), '.r')                                      % Maximum Vertical
hold on
grid

L = tv(1);
T = tv(2) - tv(1);

Kp = 1.2*T/L;
Ki = 2*L;
Ti = 2*L;
Td = 0.5*L;

cont = Kp*(1 + 1/(Ti*s) + Td*s);
     
cl_sys = feedback(cont*P_motor,1);
figure; step(cl_sys)
t = [0:0.01:3];
[yc,tc] = step(cl_sys,t);
figure;
plot(tc,yc,'LineWidth',2); xlabel('Time(s)'); ylabel('Amplitude');
title('Zeigler Nicholas Optimized Closed Loop Response');
grid on
