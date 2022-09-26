%Universidad Nacional Autonoma de Mexico
    %Instituto de Ingenieria
    %Sistema de adquisicion de datos iiDAQ
    
    clear all
    close all
    clc
    
    %---------------------------------------------------------------------
    i = 1;
    pin = 0;
    dutyCycle = 0;
    %---------------------------------------------------------------------
    
    s = connectiiDAQ(); 
    
    %---------------------------------------------------------------------
    
    %Aseguramos un valor inicial cero en el ciclo de trabajo de los pines PWM.
    
    configurePWM (s, 0, dutyCycle);
    configurePWM (s, 1, dutyCycle); 
    configurePWM (s, 2, dutyCycle); 
    
    disp('Iniciando programa...')
    pause(2)
    clc
    
    while i == 1
    
        pin = input("Elegir el pin PWM que se desea: ");
        dutyCycle = input("Colocar el valor del ciclo de trabajo: ");
        configurePWM (s, pin, dutyCycle); %Configuramos el pin PWM con el ciclo de trabajo correspondiente.
        i = input("Para intentarlo de nuevo, escribir 1, en caso contrario, escribir 0: ");
        if i == 0
            break;
        end 
    
    end 
    
   %---------------------------------------------------------------------
   
    disconnectiiDAQ(s);