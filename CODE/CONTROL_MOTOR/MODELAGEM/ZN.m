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



Kp = 1.2 / a; % Kp = 0.95 / a;
Ti = 2*T;     % Ti = 1.4*T;
Ki = Kp/Ti;
Td = 0.5*L;   % Td = 0.47*L;

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
