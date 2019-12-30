kp=1.2/a;ti=2*L;td=0.5*L;ki=kp/ti;kd=td*kp;
disp('PID gains');
disp(vpa([kp ki kd],4)),%close
nc=[kd kp ki];dc=[1 0];gc=tf(nc,dc);
nh=conv(Ka*np,nc);dh=polyadd(conv(dc,dp),nh);
h=tf(nh,dh)
nhn=conv(np,dc);hn=tf(nhn,dh,'inputdelay',tdelay)
p=roots(dh);p0=p(1);cksi_v2;
p0=p(3);cksi_v2;
dt=0.00361;ts=12.56;t=0:dt:ts;
xo=step(fd*gp,t);
hold on,plot(t,xo,'b','Linewidth',2),
xr=step(r0*h,t);xn=step(fd*hn,t);
xclsys=xr+xn;
hold on;plot(t,xclsys,'r','Linewidth',2)
legend('Control OFF','Control ON')
stepinfo(xclsys(ns:end),t(ns:end))