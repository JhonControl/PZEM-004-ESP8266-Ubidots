 
/*--------------------------------------------------------------
  Program:     PZEM-004 & ESP8266 12E + Modbus TCP/IP Slave
  
  Description:  Eiption:  Connection and communication Serial power meter Active PZEM-004
                Peacefair with Module ESP8266 view on Ubidots Platform IoT
                
                Conexión y comunicación Serial medidor de potencia Activa PZEM-004
                Peacefair con Modulo ESP8266 visualizacion en Plataforma IoT Ubidots
  
  Hardware:     ESP8266 12E NodeMCU Lolin. + Meter PZEM-004 - Peacefair
                
  Software:     Arduino IDE v1.8.3
  
  Date:         11 May 2018

  Tutorial English Complete   
  Tutorial Español Complete   
     
  Created : https://github.com/ubidots/ubidots-esp8266  
  Modified  PDAControl   http://pdacontroles.com   http://pdacontrolen.com

        
--------------------------------------------------------------*/


#include "UbidotsMicroESP8266.h"
#define TOKEN  "***-**********************"  // Put here your Ubidots TOKEN
#define WIFISSID "*********"
#define PASSWORD "**********"

#include <SoftwareSerial.h> // Arduino IDE <1.6.6

#include <PZEM004T.h> //https://github.com/olehs/PZEM004T
PZEM004T pzem(&Serial);                                        /// use Serial
IPAddress ip(192,168,1,1);

  float v_UB =0;          
  float i_UB =0;          
  float p_UB =0;        
  float e_UB =0;

Ubidots client(TOKEN);
unsigned long lastMillis = 0;

void setup(){ 
  
    client.wifiConnection(WIFISSID, PASSWORD);    
     
    pzem.setAddress(ip);

    
}
void loop(){
 
/*
         Lectura de Medidor PZEM
         PZEM Meter Reading
*/
        float v = pzem.voltage(ip);          
        if(v >= 0.0){   v_UB =v;      } //V  
        
        float c = pzem.current(ip);
        if(c >= 0.0){   i_UB = c;       } //A                                                                                                                      
        
        float p = pzem.power(ip);
        if(p >= 0.0){   p_UB =p;       } //kW
        
        float e = pzem.energy(ip);          
        if(e >= 0.0){  e_UB =e;        } //kWh    

    if (millis() - lastMillis > 15000) {  ///every 15S

   
          
            lastMillis = millis();
            
            client.add("voltage", v_UB);
            client.add("current", i_UB);
            client.add("power",   p_UB);
            client.add("energy",  e_UB);
      
            client.sendAll(true);
            
            }
   
}
