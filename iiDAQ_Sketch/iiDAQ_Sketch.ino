/*
 Universidad Nacional Autónoma de México
 Instituto de Ingeniería
 Sistema de Adquisición de Datos iiDAQ
 
 Autores:
 González-Arrieta Lizbeth 
 Rámirez-Chavarría Roberto Giovanni
 Torres-Ortiz Flor Lizeth
 Resendiz-Quintanar Areli

 Para cualquier duda o comentario: iidaq.soporte@gmail.com
*/


#include <Adafruit_ADS1X15.h>
#include <Wire.h>
#include <SPI.h>
#include <MD_AD9833.h>
#include <Adafruit_MCP4725.h>


#define DAC_ADDR 0x60
#define ADC_ADDR 0x48
#define PIN0 2
#define PIN1 3
#define PIN2 4
#define PIN3 7
#define DIG0 5
#define DIG1 6
#define DIG2 9
#define DOWN LOW
#define UP HIGH
#define FSYNC 10  ///< SPI Load pin number (FSYNC in AD9833 usage)

Adafruit_MCP4725 dac;
Adafruit_ADS1115 ads;
MD_AD9833 AD(FSYNC); // Hardware SPI

String serial_data;
int16_t dac_value=0;
int16_t adc0, adc1, adc2, adc3;
int8_t adc_mode=0;
uint8_t adc_chns=0x0F; //all channels
int16_t adc_gain=0;

// Character constants for commands
const char CMD_HELP = '?';
const char BLANK = ' ';
const char PACKET_START = ':';
const char PACKET_END = ';';
const char CMD_FREQ = 'F';
const char CMD_PHASE = 'P';
const char CMD_OUTPUT = 'O';
const char OPT_FREQ = 'F';
const char OPT_PHASE = 'P';
const char OPT_SIGNAL = 'S';
const char OPT_1 = '1';
const char OPT_2 = '2';
const char OPT_MODULATE = 'M';
const uint8_t PACKET_SIZE = 20;
// the setup function runs once when you press reset or power the board
void setup() 
{
   Serial.begin(115200);
   dac.begin(DAC_ADDR);
   ads.begin();
   dac.setVoltage(dac_value, false);
   AD.begin();
   pinMode(LED_BUILTIN, OUTPUT);    
   pinMode(DIG0, OUTPUT);
   pinMode(DIG1, OUTPUT);
   pinMode(DIG2, OUTPUT);
   pinMode(PIN0, OUTPUT);
   pinMode(PIN1, OUTPUT);
   pinMode(PIN2, OUTPUT);
   pinMode(PIN3, OUTPUT);
   TCCR1B = TCCR1B & 0b11111001; // DIG2 - PWM 31,25 kHz
   Serial.setTimeout(30);
}


// the loop function runs over and over again forever
void loop() 
{ 
  char sbuff[20];
  if(Serial.available())
  { 
      serial_data=Serial.readString();
      //DAC
      if(serial_data.startsWith("DAC"))//if(sbuff[0]=='D')
      {
        dac_value=serial_data.substring(3).toInt()&0x0FFF;
        dac.setVoltage(dac_value, false);
      } 
      //ADC
      
      else if(serial_data.startsWith("ADC"))
      {
        if(serial_data.substring(3).startsWith("MODE"))
        {
          adc_mode=serial_data.substring(7).toInt()&0x01;
        }
        else if(serial_data.substring(3).startsWith("GAIN"))
        {
          adc_gain=serial_data.substring(7).toInt()&0x07;
          if(adc_gain>5)adc_gain=5;
          adc_gain=adc_gain<<9;
          ads.setGain(adc_gain); 
          // ads.setGain(0);        // 2/3x gain +/- 6.144V  0.1875mV (default)
          // ads.setGain(512);      // 1x gain   +/- 4.096V  0.125mV
          // ads.setGain(1024);     // 2x gain   +/- 2.048V  0.0625mV
          // ads.setGain(1536);     // 4x gain   +/- 1.024V  0.03125mV
          // ads.setGain(2048);     // 8x gain   +/- 0.512V  0.015625mV
          // ads.setGain(2560);     // 16x gain  +/- 0.256V  0.0078125mV
        }
        else if(serial_data.substring(3).startsWith("CHNS"))
        {
          adc_chns=serial_data.substring(7).toInt()&0x0F;
        }
      }

      else if(serial_data.startsWith("READ")){
          adc0=adc1=adc2=adc3=0;
          if(!adc_mode)
          {
            if(adc_chns&0x01)adc0 = ads.readADC_SingleEnded(0);
            if(adc_chns&0x02)adc1 = ads.readADC_SingleEnded(1);
            if(adc_chns&0x04)adc2 = ads.readADC_SingleEnded(2);
            if(adc_chns&0x08)adc3 = ads.readADC_SingleEnded(3);
          }
          else
          {
            if(adc_chns&0x01)adc0 = ads.readADC_Differential_0_1();  
            if(adc_chns&0x02)adc1 = ads.readADC_Differential_2_3();
          }
          switch(serial_data.charAt(4))
        {
          case '0':
            Serial.print(adc0);//Serial.print(";");
            Serial.println("");
            break;
         case '1':
            Serial.print(adc1);
            Serial.println("");
            break;
         case '2':
            Serial.print(adc2);
            Serial.println("");
            break;
         case '3':
            Serial.print(adc3);
            Serial.println("");
            break;
             
        }
          }
  
      //DIG PINS/PWM
      else if(serial_data.startsWith("DIG"))
      {
        switch(serial_data.charAt(3))
        {
          case '0':
            analogWrite(DIG0, serial_data.substring(4).toInt()&0xFF);
          break;
          case '1':
            analogWrite(DIG1, serial_data.substring(4).toInt()&0xFF);
          break;
          case '2':
            analogWrite(DIG2, serial_data.substring(4).toInt()&0xFF);
          break;                   
        }
      }
// DIG PINS/OUT-IN
     /* Disponible en la siguiente versión de iiDAQ 
        else if(serial_data.startsWith("IPIN"))
      {
        switch(serial_data.charAt(4))
        {
          case '0':
             pinMode(PIN0, INPUT);
          break;
          case '1':
            pinMode(PIN1, INPUT);
          break;
          case '2':
            pinMode(PIN2, INPUT);
          break;  
          case '3':
            pinMode(PIN3, INPUT);
          break;                 
        }
      }*/
      else if(serial_data.startsWith("OPIN"))
      {
        switch(serial_data.charAt(4))
        {
          case '0':
            if(serial_data.substring(5).startsWith("H")){
                pinMode(PIN0, OUTPUT);
                digitalWrite(PIN0, UP);
            }
            if(serial_data.substring(5).startsWith("L")){
                pinMode(PIN0, OUTPUT);
                digitalWrite(PIN0, DOWN);
            } 
          break;
          case '1':
            if(serial_data.substring(5).startsWith("H")){
                pinMode(PIN1, OUTPUT);
                digitalWrite(PIN1, UP);
            }
            if(serial_data.substring(5).startsWith("L")){
                pinMode(PIN1, OUTPUT);
                digitalWrite(PIN1, DOWN);
            }
          break;
          case '2':
            if(serial_data.substring(5).startsWith("H")){
                pinMode(PIN2, OUTPUT);
                digitalWrite(PIN2, UP);
            }
            if(serial_data.substring(5).startsWith("L")){
                pinMode(PIN2, OUTPUT);
                digitalWrite(PIN2, DOWN);
            }
          break;  
          case '3':
            if(serial_data.substring(5).startsWith("H")){
                pinMode(PIN3, OUTPUT);
                digitalWrite(PIN3, UP);
            }
            if(serial_data.substring(5).startsWith("L")){
                pinMode(PIN3, OUTPUT);
                digitalWrite(PIN3, DOWN);
            }
          break;                 
        }
      }
      // FUNC
      else if(serial_data.startsWith(":"))
      {
        char cmd[20];
        String s=serial_data.substring(1, serial_data.indexOf(';'));
        s.toCharArray(cmd,s.length()+1);
        processPacket(cmd);  
      }
  
  
  // delayMicroseconds(50);  
  }

}

void processPacket(char *cp)
// Assume we have a correctly formed packet from the pasing in readPacket()
{
  uint32_t  ul;
  MD_AD9833::channel_t chan;
  MD_AD9833::mode_t mode;

  switch (*cp++)
  {
  case CMD_FREQ:
    switch (*cp++)
    {
    case OPT_1: chan = MD_AD9833::CHAN_0; break;
    case OPT_2: chan = MD_AD9833::CHAN_1; break;
    case OPT_MODULATE: /* do something in future */ break;
    }

    ul = strtoul(cp, NULL, 10);
    AD.setFrequency(chan, ul);
    break;

  case CMD_PHASE:
    switch (*cp++)
    {
    case OPT_1: chan = MD_AD9833::CHAN_0; break;
    case OPT_2: chan = MD_AD9833::CHAN_1; break;
    }

    ul = strtoul(cp, NULL, 10);
    AD.setPhase(chan, (uint16_t)ul);
    break;

  case CMD_OUTPUT:
    switch (*cp++)
    {
    case OPT_FREQ:
      switch (*cp)
      {
      case OPT_1: chan = MD_AD9833::CHAN_0; break;
      case OPT_2: chan = MD_AD9833::CHAN_1; break;
      case OPT_MODULATE: /* do something in future */ break;
      }
      AD.setActiveFrequency(chan);
      break;

    case OPT_PHASE:
      switch (*cp)
      {
      case OPT_1: chan = MD_AD9833::CHAN_0; break;
      case OPT_2: chan = MD_AD9833::CHAN_1; break;
      case OPT_MODULATE: /* do something in future */ break;
      }
      AD.setActivePhase(chan);
      break;

    case OPT_SIGNAL:
      switch (*cp)
      {
      case 'O': mode = MD_AD9833::MODE_OFF;    break;
      case 'S': mode = MD_AD9833::MODE_SINE;   break;
      case 'T': mode = MD_AD9833::MODE_TRIANGLE;  break;
      case 'Q': mode = MD_AD9833::MODE_SQUARE1;  break;
      }
      AD.setMode(mode);
      break;
    }
    break;
  }

  return;
}
