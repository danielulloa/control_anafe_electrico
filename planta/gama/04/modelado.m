clc;clear;
[y1]=importdata('plancha.dat');
[y2]=importdata('plancha2.dat');
y1=[y1;y2];
clear y2;
a1=y1(55:460);
a2=y1(508:2000);
t2=[508:1:2000]';