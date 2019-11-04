clear;clc;
[y1]=importdata('plancha.dat');
[y2]=importdata('agua.dat');
[t]=importdata('tiempo.dat');

for i=1:2000
    if (i < 950) & (i>5)
        x(i)=1500;
    else
        x(i)=0;
    end
end
x=x'

plot(t,y1,t,y2)