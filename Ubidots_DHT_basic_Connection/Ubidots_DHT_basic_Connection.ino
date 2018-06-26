 
/*--------------------------------------------------------------
  Program:      Connection ESP8266 + DHT11 Sensor and IoT Ubidots platform

  Description:  Every 10 seconds the module esp8266 will perform the reading 
                of the DHT sensor and send the temperature and relative humidity to Ubidots

                Cada 10 segundos el modulo esp8266 realizara la lectura del 
                sensor DHT y enviara la temperatura y humedad relativa a Ubidots
  
  Hardware:     ESP8266 12E NodeMCU Lolin. + Sensor DHT (Temperature/Hum)
                
  Software:     Arduino IDE v1.8.3
  
  Date:         17 Dic 2017

  Tutorial English Complete   http://pdacontrolen.com/tutorial-platform-iot-ubidots-esp8266-sensor-dht11/
  Tutorial Español Complete   http://pdacontroles.com/tutorial-plataforma-iot-ubidots-esp8266-sensor-dht11/
     
  Created : https://github.com/ubidots/ubidots-esp8266  
  Modified  PDAControl   http://pdacontroles.com   http://pdacontrolen.com

        
--------------------------------------------------------------*/

#include "DHT.h" 
#define DHTPIN 14
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);


#include "UbidotsMicroESP8266.h"
#define TOKEN  "A1E-***********************"  // Put here your Ubidots TOKEN
#define WIFISSID "************"
#define PASSWORD "***********"

Ubidots client(TOKEN);
unsigned long lastMillis = 0;

void setup(){
    Serial.begin(115200);
    dht.begin();
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);
}
void loop(){

    if (millis() - lastMillis > 10000) {  ///every 10S

      float humedad = dht.readHumidity();
      float temperatura = dht.readTemperature();
      
            lastMillis = millis();
            client.add("humrel", humedad);
            client.add("temperature", temperatura);
            client.sendAll(true);
            
            }
   
}
