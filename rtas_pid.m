fileID=fopen('pid025_kp4.3_ti230_td16.txt', 'r');
%M = textscan(fileID, '%{HH:mm:ss.SSS}D %f %f %f %f','delimiter','\t');
M = textscan(fileID, '%f %f','delimiter','\t');
t=M(:,2);
temp=cell2mat(M(:,1));
temp=smooth(temp,50);
plot(temp)
hold on
line('XData', [0 size(temp,1)], 'YData', [120 120], 'LineStyle', '-','LineWidth', 2, 'Color','m')
%plot(ScopeData(:,3))