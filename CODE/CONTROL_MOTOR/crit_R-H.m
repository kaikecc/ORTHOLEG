clc

P_motor = Km /(Jeq*La*s^2 + (Jeq*Ra + beq*La)*s + beq*Ra + Km^2);

den = (Jeq*La*s^2 + (Jeq*Ra + beq*La)*s + beq*Ra + Km^2 + Kp*Km);

Kp = -(beq*Ra + Km^2) / Km;