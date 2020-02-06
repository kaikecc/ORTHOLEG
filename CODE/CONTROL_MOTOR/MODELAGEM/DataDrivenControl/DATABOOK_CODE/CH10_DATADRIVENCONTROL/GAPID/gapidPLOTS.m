clear all, close all, clc

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

a = Jeq*La;
b = Jeq*Ra + beq*La;
c = beq*Ra + Km^2;

%Km = Km/a;
%b = b/a;
%c = c/a;
%a = a/a;


%P_motor = Km /(a*s*s + b*s + c);

%**************************************************************************
dt = 0.001;
popsize = 25;
MaxGenerations = 10;
s = tf('s');
%G = 1/(s*(s*s+s+1));
G = Km / (J1*La*s*s + (J1*Ra + b1*La)*s + Km*Km);
rng(1,'twister') % for reproducibility

% population = rand(popsize,3);
load randpop.mat

options = optimoptions(@ga,'PopulationSize',popsize,'MaxGenerations',MaxGenerations,'InitialPopulation',population,'OutputFcn',@myfun);
[x,fval,exitflag,output,population,scores] = ga(@(K)pidtest(G,dt,K),3,-eye(3),zeros(3,1),[],[],[],[],[],options);

%%
load history.mat
for k=1:MaxGenerations
    sortedcost(:,k) = sort(cost(:,k));
end
imagesc(log(sortedcost(:,1:MaxGenerations)))
colorbar
set(gcf,'Position',[100 100 600 300])
set(gcf,'PaperPositionMode','auto')
print('-deps2', '-loose', '../../figures/GAPID1');
%%
figure
    hold on
    for k=1:MaxGenerations
        for j=1:popsize
            scatter3(history(j,1,k),history(j,2,k),history(j,3,k),15,[(MaxGenerations-k)/MaxGenerations 0.25 k/MaxGenerations],'filled');
        end
    end
      [B,I] = sort(cost(:,MaxGenerations));  
      scatter3(history(I(1),1,MaxGenerations),history(I(1),2,MaxGenerations),history(I(1),3,MaxGenerations),100,[0 0 0],'filled')
        view(69,24)
    box on
    xlabel('P')
    ylabel('I')
    zlabel('D')
set(gcf,'Position',[100 100 350 250])
set(gcf,'PaperPositionMode','auto')
print('-deps2', '-loose', '../../figures/GAPID2');
%% Plot Generation 1
gen = 1;
t = 0:dt:20;
s = tf('s');
figure
hold on
for k=1:popsize
    K = history(k,1,gen) + history(k,2,gen)/s + history(k,3,gen)*s/(1+.001*s);
    L = series(K,G);
    CL = feedback(L,1);
    [y,t] = step(CL,t);
    plot(t,y,'LineWidth',1.2);
end
box on, grid on
set(gcf,'Position',[100 100 550 250])
set(gcf,'PaperPositionMode','auto')
print('-deps2', '-loose', '../../figures/GAPID3');

%% Plot Generation 10
gen = 10;
t = 0:dt:20;
s = tf('s');
figure
hold on
for k=1:popsize
    K = history(k,1,gen) + history(k,2,gen)/s + history(k,3,gen)*s/(1+.001*s);
    L = series(K,G);
    CL = feedback(L,1);
    [y,t] = step(CL,t);
    plot(t,y,'LineWidth',1.2);
end
box on, grid on
set(gcf,'Position',[100 100 550 250])
set(gcf,'PaperPositionMode','auto')
print('-deps2', '-loose', '../../figures/GAPID4');
%% Plot BEST of each Generation
figure
for gen=1:MaxGenerations
    [B,I] = sort(cost(:,gen));
    K = history(I(1),1,gen) + history(I(1),2,gen)/s + history(I(1),3,gen)*s/(1+.001*s);
    L = series(K,G);
    CL = feedback(L,1);
    [y,t] = step(CL,t);
    subplot(3,1,1), hold on
    plot(t,y,'LineWidth',1+.1*gen,'Color',[(MaxGenerations-gen)/MaxGenerations 0 gen/MaxGenerations],'LineWidth',1.2);
    box on, grid on
    subplot(3,1,2), hold on
    CTRLtf = K/(1+K*G);
    u = lsim(K,1-y,t);
    plot(t,u,'LineWidth',1+.1*gen,'Color',[(MaxGenerations-gen)/MaxGenerations 0 gen/MaxGenerations],'LineWidth',1.2);
    ylim([-1 2])
    box on, grid on
    subplot(3,1,3), hold on
    Q = 1;
    R = .001;
    J = dt*cumsum(Q*(1-y(:)).^2 + R*u(:).^2);
    plot(t,J,'LineWidth',1+.1*gen,'Color',[(MaxGenerations-gen)/MaxGenerations 0 gen/MaxGenerations],'LineWidth',1.2);
end
box on, grid on
set(gcf,'Position',[100 100 550 350])
set(gcf,'PaperPositionMode','auto')
print('-deps2', '-loose', '../../figures/GAPID5');