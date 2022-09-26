%Universidad Nacional Autonoma de Mexico
    %Instituto de Ingenieria
    %Sistema de adquisicion de datos iiDAQ
    
    clear all
    close all
    clc
    
    %---------------------------------------------------------------------
    
    value = 0; 
    pin = 0; 
    mode = 0; 
    gain = 1; 
    N = 100; %Numero de muestras
    ii = 1; 
    A0 = 0;
    
    %---------------------------------------------------------------------
    
    s = connectiiDAQ(); 
    
    %---------------------------------------------------------------------
    
    %Aseguramos un valor inicial cero en la salida del DAC
    disp('Iniciando programa...')
    configureDAC (s, value);
    
        value = input("Elegir el voltaje de salida para el DAC en bits: ");
        configureDAC (s, value); %Configuramos el voltaje de salida.
        
        %A continuacion, se realizaran las lecturas del circuito
        clc
        disp("Obteniendo mediciones del circuito...");
        
        for ii=1:N
            VR1(ii) =  ((analogRead(s, A0)*3.3)/17000); %Se multiplica por 
                                                        %factor de
                                                        %conversion
            plot(VR1)
            drawnow
        end
        
        disp ("Mediciones obtenidas");
        pause (1);
      
        figure
        plot (VR1, 'LineWidth',1,'Color','#A2142F');
        ylabel('Voltaje (V)')
        xlabel('Muestra')
        legend('Voltaje Potenciómetro','Location', 'Best')
   %---------------------------------------------------------------------
   
    disconnectiiDAQ(s);