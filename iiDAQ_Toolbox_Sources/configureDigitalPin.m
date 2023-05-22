function configureDigitalPin(s, digitalPin, value, type)
    switch type
        case 0
            disp('Esta configuración estará disponible en la siguiente versión de iiDAQ');
        case 1
            disp('Configurando pin digital...');
            switch digitalPin
                case 0
                    if value == 1
                        fprintf(s, 'OPIN0H');
                        pause(2)
                        disp('Pin digital 0, Tipo: Salida, Valor lógico: 1');
                    end
                    if value == 0
                        fprintf(s, 'OPIN0L');
                        pause(2)
                        disp('Pin digital 0, Tipo: Salida, Valor lógico: 0');
                    end
                case 1
                    if value == 1
                        fprintf(s, 'OPIN1H');
                        pause(2)
                        disp('Pin digital 1, Tipo: Salida, Valor lógico: 1');
                    end
                    if value == 0
                        fprintf(s, 'OPIN1L');
                        pause(2)
                        disp('Pin digital 1, Tipo: Salida, Valor lógico: 0');
                    end

                case 2
                    if value == 1
                        fprintf(s, 'OPIN2H');
                        pause(2)
                        disp('Pin digital 2, Tipo: Salida, Valor lógico: 1');
                    end
                    if value == 0
                        fprintf(s, 'OPIN2L');
                        pause(2)
                        disp('Pin digital 2, Tipo: Salida, Valor lógico: 0');
                    end

                case 3
                    if value == 1
                        fprintf(s, 'OPIN3H');
                        pause(2)
                        disp('Pin digital 3, Tipo: Salida, Valor lógico: 1');
                    end
                    if value == 0
                        fprintf(s, 'OPIN3L');
                        pause(2)
                        disp('Pin digital 3, Tipo: Salida, Valor lógico: 0');
                    end
                otherwise
                    disp('El pin digital no se seleccionó correctamente');
            end
        otherwise
            disp('El tipo de pin digital no se configuró correctamente'); 
    end    
end

