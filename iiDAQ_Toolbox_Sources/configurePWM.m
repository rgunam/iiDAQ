function configurePWM (s, pin, dutyCycle)
    arrPWM{1,1}= num2str(round((dutyCycle*255)/100));
    pinEnable = pin;
    switch pinEnable
        case 0
            fprintf(s,strcat('DIG0',cell2mat(arrPWM(1))));
            disp ('Pin PWM 0 configurado correctamente');
        case 1
            fprintf(s,strcat('DIG1',cell2mat(arrPWM(1))));
            disp ('Pin PWM 1 configurado correctamente');
        case 2
            fprintf(s,strcat('DIG2',cell2mat(arrPWM(1))));
            disp ('Pin PWM 2 configurado correctamente');
    end
end
