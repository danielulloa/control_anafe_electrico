fileID=fopen('segundo_pid.txt', 'r');
%M = textscan(fileID, '%{HH:mm:ss.SSS}D %f %f %f %f %f','delimiter','\t');
%out1=cell2mat(M(:,2));
%out2=cell2mat(M(:,6));

M = textscan(fileID, '%f %f %f %f %f','delimiter','\t');
out1=cell2mat(M(:,1));
out2=cell2mat(M(:,5));
plot(out1)
hold on
plot(out2)
line('XData', [0 size(out1,1)], 'YData', [80 80], 'LineStyle', '-','LineWidth', 2, 'Color','m')
hold off