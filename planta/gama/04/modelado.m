clc;clear;
[y1]=importdata('plancha.dat');
%[y2]=importdata('plancha2.dat');
%y1=[y1;y2];
clear y2;
%a1=y1(55:460);
%a2=y1(508:2000);
%t2=[508:1:2000]';
%plot(y1)
alpha=35;
tau=220;
k=550
planta=tf([k],[tau 1],'InputDelay',alpha)
%step(planta)
%hold on
%plot(y1,'g')
g=0.005
step(feedback(planta*g,1))