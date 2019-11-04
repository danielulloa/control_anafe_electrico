%function recepcion(muestras)
    muestras=10;
    delete(instrfind({'Port'},{'COM4'})); %%Modificar puerto
    a=serial('com4');
    fclose(a);
    set(a,'BaudRate',250000);
    fopen(a);%%Inicializa puerto
    A=fscanf(a,'%f');
    s=0;

    for i=1:(muestras)
        A=fscanf(a,'%f');
        temp(i)=A(1,1);
        accion(i)=A(2,1);
        figure(1)
        plot(temp(i),'g');
        ylim([0 130]);
        xlim([0 muestras]);
        title('hola');
        hold on; %Esto va siempre?
        drawnow;
    end
clf;    
fclose(a);
delete(a);

%%Genero los archivos .dat
dlmwrite('temp.dat', temp, 'delimiter', '\n', 'precision', '%.3f');
dlmwrite('accion.dat', accion, 'delimiter', '\n', 'precision', '%.3f');
%end