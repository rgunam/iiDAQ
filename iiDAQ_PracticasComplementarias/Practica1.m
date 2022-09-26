    %Universidad Nacional Autonoma de Mexico
    %Instituto de Ingenieria
    %Sistema de adquisicion de datos iiDAQ
    
    clear all
    close all
    clc
    
    %---------------------------------------------------------------------
    i = 1; 
    digitalPin = 0;
    value = 0;
    typePin = 1;
    %---------------------------------------------------------------------4
    
    s = connectiiDAQ(); 
    
    %---------------------------------------------------------------------
    
    %Aseguramos un valor inicial logico cero en todos los pines.
    
    configureDigitalPin (s, 0, value, typePin); 
    configureDigitalPin (s, 1, value, typePin); 
    configureDigitalPin (s, 2, value, typePin); 
    configureDigitalPin (s, 3, value, typePin);
    
    disp('Iniciando programa...')
    pause(2)
    clc
    
    while i == 1
    
        digitalPin = input("Elegir el pin digital que se desea: ");
        value = input("Colocar el valor lógico de salida: ");
        configureDigitalPin (s, digitalPin, value, typePin); %Configuramos el pin digital para encender o apagar el led.
        i = input("Para intentarlo de nuevo, escribir 1, en caso contrario, escribir 0: ");
        if i == 0
            break;
        end
    
    end 
    
   %---------------------------------------------------------------------
    disconnectiiDAQ(s);