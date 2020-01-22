clear all, close all, clc

% Dados do motor
Kt = 30.2 * 1E-3;  % Constante de Torque do Motor (m.N / A)
Kb = 30 / 317*pi;  % back emf constant (V.s / rad)
Ra = 0.299;        % Resistência do Motor (R)
La = 0.082 * 1E-3; % Indutância do Motor (H)
J1 = 14.2 * 1E-6;  % Momento de Inércia do Motor (kg.m^3)
tq1 = 177 * 1E-3;  % Torque Nominal do Motor (m.N)
v1 = 6940*(pi/30); % Velocidade Angular Nominal do Motor (rad / s) 
b1 = 1 / (((3.14 / 1E-3) * pi) / 30);  % Coeficiente de Viscosidade do Motor (m.N / rad/s) 

% Dados da Caixa de Redução
N1 = 8;
N2 = 343;

J2 = 15 * 1E-6; % Momento de Inércia da Caixa de Redução (kg.m^3)
tq2 = 15; % Torque da Caixa de Redução Max. continuous torque (m.N)
v2 = v1 / N2; % Velocidade da Caixa da Redução
b2 = tq2 / v2; % Coeficiente de Viscosidade da Caixa de Redução

% Equivalentes

Jeq = J1 + J2*(N1/N2)^2; % equivalente de cap em paral se soma
beq = b1 + b2*(N1/N2)^2; % equivalente

s = tf('s');

a = J1*La;
b = (J1*Ra + b1*La);
c =  b1*Ra + Kb*Kt;

%b = b/a;
%c = c/a;
%a = a/a;

P_motor = Kt /(a*s*s + b*s + c);

%P_motor = Kt / ((Jeq*Ra + beq*La)*s + beq*Ra + Kb*Kt);

%P_motor = 0.015 / (0.01*s*s + 0.14*s + 0.40015);
% Find the root using FZERO

format long

[y,t] = step(P_motor);
h = mean(diff(t));
dy = gradient(y, h);                                                % Numerical Derivative
[~,idx] = max(dy);                                                  % Index Of Maximum
b = [t([idx-1,idx+1]) ones(2,1)] \ y([idx-1,idx+1]);                % Regression Line Around Maximum Derivative
tv = [-b(2)/b(1); (1-b(2))/b(1)];                                   % Independent Variable Range For Tangent Line Plot
f = [tv ones(2,1)] * b;                                             % Calculate Tangent Line

x = ((max(y) - f(1)) / ((f(1) - y(idx))/(tv(1) - t(idx)))) + tv(1); %  para achar o ponto de T no eixo x
K = max(y);                                                         % para desenhar a reta
r = (((K - y(idx))/(x - t(idx)))*(t - x)) + K;                      % Função da reta

figure

plot(t, y)
hold on
plot(t, r, '-r','LineWidth',1.5)% Tangent Line                                           
plot(t(idx), y(idx), '.g')      % Maximum Vertical
hold on; grid on;


L = tv(1);
T = x - tv(1);
K = dcgain(P_motor);
a = (L*K) / T;

Kp = 0.95 / a;
Ti = 2.4 * T;
Td = 0.42 * L;

%Kp = 1.2 / a; % Kp = 0.95 / a;
%Ti = 2*T;     % Ti = 1.4*T;
Ki = Kp/Ti;
%Td = 0.5*L;   % Td = 0.47*L;

Kd = Kp*Td;

cont = Kp*(1 + 1/(Ti*s) + Td*s);
     
cl_sys = feedback(cont*P_motor,1);

stepinfo(step(cl_sys))

figure; step(cl_sys)
t = [0:0.01:3];
[yc,tc] = step(cl_sys,t);
figure;
plot(tc,yc,'LineWidth',2); xlabel('Time(s)'); ylabel('Amplitude');
title('Zeigler Nicholas Optimized Closed Loop Response');
grid on
