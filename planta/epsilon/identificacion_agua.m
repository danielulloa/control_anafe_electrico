load("in0.mat")
load("tagua.mat")
load("time.mat")
in0=in0.*100;
%Ts=[];
%data = iddata(in0,out2,0.5);
%data.InputName='escalón';
%data.InputUnit='V';
%data.OutputName='Temperatura agua';
%data.OutputUnit='C';
%data.TimeUnit='seconds';
%plot(data)
%sysTF=tfest(data,1,0,nan)
%compare(data,sysTF)
plot(time,out2)
hold on
alpha=185
%tau=378;
%k=100;
tau=1600
k=250;
planta=tf([k],[tau 1],'InputDelay',alpha)
step(22+planta)
hold off