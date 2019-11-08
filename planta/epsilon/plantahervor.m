fileID=fopen('planta_agua_hervor.txt', 'r');
M = textscan(fileID, '%f %f %f %f %f %f','delimiter','\t','headerlines',2);
%TIME	INPUT	OUTPUT1	OUTPUT2	TS	GRADIENT
time=cell2mat(M(:,1));
time=time.*1e-3;
in0=cell2mat(M(:,2));
out1=cell2mat(M(:,3));
out2=cell2mat(M(:,4));
loop=cell2mat(M(:,5));
gradiente=cell2mat(M(:,6));
