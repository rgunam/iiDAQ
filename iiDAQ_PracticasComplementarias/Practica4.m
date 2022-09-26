%Universidad Nacional Autonoma de Mexico
    %Instituto de Ingenieria
    %Sistema de adquisicion de datos iiDAQ
    
    clear all
    close all
    clc
    
    %---------------------------------------------------------------------
    
    channel = 0;
    Frequency = 0;
    phase = 0;
    i = 1;
    
    %---------------------------------------------------------------------
    
    s = connectiiDAQ(); 
    
    %---------------------------------------------------------------------
    
    %Aseguramos una configuración inicial
    
    
    
    signalGenerator (s, channel, "Sine", Frequency, phase); 
    disp('Iniciando programa...');
    pause (2);
    clc
    
    while i == 1   
        channel = input("Elegir el canal de salida: ");
        waveForm = input ("Selecciona la forma de onda: ");
        Frequency = input("Escribir el valor de frecuencia en la onda: ");
        phase = input("Escribir el valor de fase en la onda: ");
        
        signalGenerator(s, channel, waveForm, Frequency, phase); %Se configura el generador de señales para obtener el resultado en el osciloscopio.
        
        i = input("Para intentarlo de nuevo, escribir 1, en caso contrario, escribir 0: ");
       
        if i == 0
            break;
        end 
    
    end 
    
   %---------------------------------------------------------------------
   
    disconnectiiDAQ(s);