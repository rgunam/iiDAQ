function s = connectiiDAQ (serialPort)
    serialPortList = serialPort;
    if serialPort ~= ""        
        baudRate = 115200;
        s = serial(serialPortList,'Baudrate',baudRate,'Terminator','CR/LF');
        fopen(s);
        disp('Dispositivo conectado');
        pause(2)
    else
        disp ('No se encuentra dispositivo conectado');
    end
end

