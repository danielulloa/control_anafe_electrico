function recepcion(muestras)
    delete(instrfind({'Port'},{'COM3'})); %%Modificar puerto
    a=serial('com3');
    set(a,'BaudRate',9600);
    fopen(a);%%Inicializa puerto
    A=fscanf(a,'%f');
    s=0;

    for i=1:(muestras)
        A=fscanf(a,'%f');
        t(i)=A(1,1);
        plancha(i)=A(2,1);
        agua(i)=A(3,1);
        figure(1)
        plot(i,plancha(i),'^g',i,agua(i),'dr');
        ylim([0 500]);
        xlim([0 muestras]);
        title('hola');
        hold on; %Esto va siempre?
        drawnow;
    end
    
fclose(a);
delete(a);

%%Genero los archivos .dat
dlmwrite('tiempo.dat', t, 'delimiter', '\n', 'precision', '%.3f');
dlmwrite('plancha.dat', plancha, 'delimiter', '\n', 'precision', '%.3f');
dlmwrite('agua.dat', agua, 'delimiter', '\n', 'precision', '%.3f');
end