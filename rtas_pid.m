fileID=fopen('pid05_k2.txt', 'r');
M = textscan(fileID, '%{HH:mm:ss.SSS}D %f %f %f %f','delimiter','\t');
t=M(:,1);
temp=cell2mat(M(:,2));
plot(temp)
line('XData', [0 size(temp,1)], 'YData', [120 120], 'LineStyle', '-','LineWidth', 2, 'Color','m')