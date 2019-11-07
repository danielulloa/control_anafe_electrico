fileID=fopen('plancha_01.txt', 'r');
%TIME	INPUT	OUTPUT1	OUTPUT2	TS	GRADIENT
%M = textscan(fileID, '%d %d %f %f %d %f','delimiter','\t', 'headerlines',4);
M = textscan(fileID, '%d %f %f %f %f','delimiter','\t', 'headerlines',4);
%TIME	INPUT	OUTPUT	TS	GRADIENT
t=cell2mat(M(:,1));
delay=cell2mat(M(:,4));
ts=median(delay);
ts=ts*1e-3;
t1=0:ts:(size(t,1)-1)*ts;
t1=t1';
in0=cell2mat(M(:,2));
in0(find(t==203512):end)=0;
out1=cell2mat(M(:,3));
%out2=cell2mat(M(:,4));

grad=cell2mat(M(:,5));
%plot(in0*220)
%hold on
%plot(out1)
%plot(out2)
%grid
alpha=(find(out1>25,1,'first')-find(in0==1,1,'first'))*ts;
alpha=25
tau=580;
k=950;
planta=tf([k],[tau 1],'InputDelay',alpha)
step(23.5+planta)
hold on
plot(t1,out1,'g')
hold off

alpha=25
tau=300;
k=650;
plot(t1,((k-k*exp(-t1/tau)).*heaviside(t1-alpha))-23.5)
hold on
plot(t1,out1,'g')