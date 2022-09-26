%Universidad Nacional Autónoma de México
%Instituto de Ingeniería
%Sistema de adquisición de datos iiDAQ
    
%Las siguientes tres líneas de comando son para descartar variables y 
%objetos utilizados en programas anteriores.
    
clear all
close all
clc
    
%-----------------------------------------------------------------------
    
%Programar en este apartado, en caso de ser necesario, la asignación de 
%variables o líneas de código necesarias antes de la conexión del sistema 
%de adquisición de datos iiDAQ.
   
%-----------------------------------------------------------------------
    
%En este apartado, se procede a conectar el sistema.
    
s = connectiiDAQ(); 
    
%-----------------------------------------------------------------------
    
%En este apartado, programar las funciones presentadas en el manual de 
%usuario, para la configuración y uso de los módulos  y puertos disponibles
%en el sistema.
    
%-----------------------------------------------------------------------
    
%En este apartado, se procede a desconectar el sistema.
    
disconnectiiDAQ(s); 