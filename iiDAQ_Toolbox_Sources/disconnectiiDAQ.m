function disconnectiiDAQ (s)
    fclose(s);
    delete(s);
    clear s serialPort;
    disp('Dispositivo Desconectado');
end