fileID=fopen('pid025hz_k3.7_Ti50.txt', 'r');
M = textscan(fileID, '%{HH:mm:ss.SSS}D %f %f %f %f','delimiter','\t');
t=M(:,1);
temp=cell2mat(M(:,2));
temp=smooth(temp,50);
plot(temp)
hold on
line('XData', [0 size(temp,1)], 'YData', [120 120], 'LineStyle', '-','LineWidth', 2, 'Color','m')
%plot(ScopeData(:,3))