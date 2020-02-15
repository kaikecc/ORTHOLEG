


zpk(P_motor)

Ts = 0.01;
dP_motor = c2d(P_motor, Ts, 'zoh');
zpk(dP_motor)

dP_motor = minreal(dP_motor,0.01);
zpk(dP_motor)

sys_cl = feedback(dP_motor,1);
[x1,t] = step(sys_cl,.9);
stairs(t,x1)
xlabel('Time (seconds)')
ylabel('Position (radians)')
title('Stairstep Response: Original')
grid

controlSystemDesigner('rlocus',dP_motor) 

dist_cl = feedback(dP_motor,C);
         [x2,t] = step(dist_cl,2);
         stairs(t,x2)
         xlabel('Time (seconds)')
         ylabel('Position (rad)')
         title('Stairstep Disturbance Response with Compensation')
         grid



