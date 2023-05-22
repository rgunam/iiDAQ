function configureDAC(s, value)
    arrDAC{1,1}= num2str(value);
    fprintf(s,strcat('DAC',cell2mat(arrDAC(1))));
    pause (100/1000)
    disp('Valor configurado correctamente');
end
