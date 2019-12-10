clc
clear all

Km = 30.2 * 1E-3;
Ra = 0.299;
La = 0.082 * 1E-3;
J = 14.2 * 1E-6;
b = (177*1E-3)/(6940*(%pi/30));


s = poly(0,'s');

num = Km;
den = (J*La*s.^2 + (J*Ra + b*La)*s + b*Ra + Km^2);

tf = num / den;

t = 0:.05:5;

gs = csim('step',t,tf);
nyquist(tf)
plot(t,gs)
xgrid

[wn,z] = damp(tf) // Frequências naturais e fatores de amortecimento.

evans(tf);

// https://en.wikibooks.org/wiki/Control_Systems/Open_source_tools/Scilab       
